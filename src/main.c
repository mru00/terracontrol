/* 
 * terrarium control
 * mru, november 2009
 *
 * using these sources:
 *   - http://www.mikrocontroller.net/topic/12185 (clock)
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/wdt.h>
#include <avr/sleep.h>


#include "common.h"


#define UART_BAUD_RATE     38400
#define TMP101_ID 1

uint8_t temp = 0;
uint8_t humidity;
uint8_t humidity_setpoint[2];
uint8_t temp_setpoint[2];
time_t  daytime[2];
char* controller_title[CONTROLER_TITLE_LEN];
uint8_t output_values = 0;
uint8_t reset_reason = 0;

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
  uint8_t dt = time_is_daytime();
  uint8_t heating_output;

  const uint8_t hyst_temp = 1;
  const uint8_t hyst_humidity = 5;

  char buf[9];

  static uint8_t counter = 0;
  static uint8_t page = 0;


  humidity = sht11_get_humidity();
  temp = sht11_get_temperature();
  
  // resets the output_values, so this must be the first here
  timeswitch_check();

  if ( dt == DAY ) heating_output = OUTPUT_HEATING_LAMP;
  else  heating_output = OUTPUT_HEATING_WIRE;

  if ( temp < temp_setpoint[dt] ) heating_on = 1;
  else if ( temp > temp_setpoint[dt] + hyst_temp) heating_on = 0;

  if ( humidity < humidity_setpoint[dt] ) fogger_on = 1;
  else if ( humidity > humidity_setpoint[dt] + hyst_humidity) fogger_on = 0;

  // heating and fogger only when necessary
  output_values |= heating_on << heating_output;
  output_values |= fogger_on << OUTPUT_FOGGER;

  pcf8574a_set(output_values);

  hd4478_clear();

  hd4478_puts(itoa8(temp, buf));
  hd4478_puts(DEGREE_SYMBOL " ");


  hd4478_puts(itoa8(humidity, buf));
  hd4478_puts("%");

  hd4478_moveto(1, 0);

  switch(page) {
  case 0:
	
	if ( reset_reason & WDRF ) {
	  hd4478_puts("WDT RESET");
	}
	else {
	  hd4478_puts(ttoa(time_now(), buf));
	}

	if ( counter++ == 3 ) {
	  page = 1;
	  counter = 0;
	}
	break;
  case 1:
	hd4478_puts((const char*)controller_title);
	if ( counter++ == 3 ) {
	  page = 0;
	  counter = 0;
	}
	break;
  }

}



int main(void)
{
  unsigned int input;

  _delay_ms(100);

  // init section -------------------------------------

  reset_reason = MCUCSR;

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
  pcf8574a_init();

  hd4478_moveto(0, 0);
  hd4478_puts("Starting");

  selftest_perform();

  wdt_enable(WDTO_2S);

  set_sleep_mode(SLEEP_MODE_IDLE);

  // main loop section ----------------------------------

  for(;;) {

	input = uart_getc();

	if ( input != UART_NO_DATA ) 
	  commandline_addchar(input & 0xff);

	if ( time_updated() ) 
	  update();

	sleep_mode();
	wdt_reset();
  }

}



