/* 
 * terrarium control
 * mru, november 2009
 *
 * using these sources:
 *   - http://www.mikrocontroller.net/topic/12185 (clock)
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <avr/wdt.h>
#include <util/delay.h>


#include "common.h"


#define UART_BAUD_RATE     38400
#define TMP101_ID 1


uint8_t temp = 0;
uint8_t humidity;
uint8_t humidity_setpoint[2];
uint8_t temp_setpoint[2];
time_t  daytime[2];


static void init_ports(void) {
  DDRD = 0xff;
  DDRB = 0xff;
  DDRC = 0xff;
  PORTC = 0x00;
}

void __attribute__((constructor)) 
uart_constructor(void) {
  uart_init(UART_BAUD_SELECT(UART_BAUD_RATE,XTAL));
}



// called every second, perform output updates
void update(void) {


  uint8_t heating_on = 0;
  uint8_t fogger_on = 0;
  uint8_t output_values = 0;
  uint8_t dt = time_is_daytime();
  uint8_t heating_output;


  const uint8_t hyst_temp = 1;
  const uint8_t hyst_humidity = 5;


  humidity = sht11_get_humidity();
  temp = sht11_get_temperature();
  
  timeswitch_check(time_now(), &output_values);

  if ( dt == DAY ) heating_output = OUTPUT_HEATING_LAMP;
  else  heating_output = OUTPUT_HEATING_WIRE;

  if ( temp < temp_setpoint[dt] ) heating_on = 1;
  else if ( temp > temp_setpoint[dt] + hyst_temp) heating_on = 0;

  if ( humidity < humidity_setpoint[dt] ) fogger_on = 1;
  else if ( humidity > humidity_setpoint[dt] + hyst_humidity) fogger_on = 0;

  // heating and fogger only when necessary
  output_values |= heating_on << heating_output;
  output_values |= fogger_on << OUTPUT_FOGGER;

  // set all pins that were handled by the timers
  for ( uint8_t j = OUTPUT_FIRST; j < OUTPUT_LAST; j++ )
	portmap_setpin(output_values & _BV(j), j);

}



int main(void)
{
  unsigned int input;

  _delay_ms(100);


  // init section -------------------------------------

  eeprom_init();

  sei();

  portmap_init();
  init_ports();
  time_init();

  timeswitch_init();

  i2c_init();
  ds1307_init();
  tmp101_init(TMP101_ID);
  commandline_init();
  hd4478_init();
  sht11_init();

  selftest_perform();

  // initialization complete.

  uart_puts(NEWLINE "TerraControl, mru 2009" NEWLINE NEWLINE);




  // main loop section ----------------------------------

  for(;;) {

	input = uart_getc();

	if ( input != UART_NO_DATA ) 
	  commandline_addchar(input & 0xff);

	if ( time_updated() ) 
	  update();
  }

}



