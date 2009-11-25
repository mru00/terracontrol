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


uint8_t volatile temp = 0;
uint8_t volatile humidity;
uint8_t volatile humidity_setpoint[2];
uint8_t volatile temp_setpoint[2];
time_t  volatile daytime[2];



char* itoa8(uint8_t value, char* buf) {

  uint8_t h, t, o;
  h = value / 100;
  t = (value - 100*h) / 10;
  o = (value - 100*h - 10*t);

  if ( h != 0 ) {
	buf[0] = '0' + h; 
	buf[1] = '0' + t;
	buf[2] = '0' + o;
	buf[3] = '\0';
  }
  else if ( t != 0 ) {
	buf[0] = '0' + t;
	buf[1] = '0' + o;
	buf[2] = '\0';
  }
  else {
	buf[0] = '0' + o;
	buf[1] = '\0';
  }

  return buf;
}


char* itoat(uint8_t value, char* buf) {

  uint8_t t, o;
  t = value / 10;
  o = (value - 10*t);

  buf[0] = '0' + t;
  buf[1] = '0' + o;
  buf[2] = '\0';

  return buf;
}

uint8_t __attribute__((pure))
atoi8(char* buf) {

  uint8_t value;

  value = 0;
  while( is_digit(*buf) ) {
	value *= 10;
	value += *buf - '0';
	buf++;
  }

  return value;
}


static inline void init_ports(void) {
  DDRD = 0xff;
  DDRB = 0xff;
  DDRC = 0xff;
  PORTC = 0x00;
}

void __attribute__((constructor)) 
uart_constructor(void) {
  uart_init(UART_BAUD_SELECT(UART_BAUD_RATE,XTAL));
}


int main(void)
{
  unsigned int input;
  uint8_t heating_on = 0;
  uint8_t fogger_on = 0;

  const uint8_t hyst_temp = 1;
  const uint8_t hyst_humidity = 5;

  _delay_ms(100);

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

  selftest_perform();


  uart_puts(NEWLINE "TerraControl, mru 2009" NEWLINE NEWLINE);


  for(;;) {

	input = uart_getc();

	if ( input != UART_NO_DATA ) {
	  commandline_addchar(input & 0xff);
	}

	if ( time_updated() ) { 

	  temp = tmp101_gettemp(TMP101_ID);
	  timeswitch_check(time_now());

	}

	uint8_t dt = time_is_daytime();
	uint8_t heating_output;

	if ( dt == DAY ) heating_output = OUTPUT_HEATING_LAMP;
	else  heating_output = OUTPUT_HEATING_WIRE;


	if ( heating_on == 0 && temp < temp_setpoint[dt] ) heating_on = 1;
	else if ( heating_on == 1 && temp > temp_setpoint[dt] + hyst_temp) heating_on = 0;

	if ( fogger_on == 0 && humidity < humidity_setpoint[dt] ) fogger_on = 1;
	else if ( fogger_on == 1 && humidity > humidity_setpoint[dt] + hyst_humidity) fogger_on = 0;

	portmap_setpin(fogger_on, OUTPUT_FOGGER);
	portmap_setpin(heating_on, heating_output);

  }
}



