
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

#include <stdio.h>
#include "common.h"


#define UART_BAUD_RATE     38400
#define TMP101_ID 1





uint8_t temp = 0;
uint8_t temp_setpoint;
uint8_t humidity;
uint8_t humidity_setpoint;

// wrapper for fdevopen
int uart_fdev(char c, FILE* x) {
  uart_putc((unsigned char)c);
  return 0;
}

static void init_ports(void) {
  DDRD = 0xff;
  DDRB = 0xff;
  DDRC = 0xff;
  PORTC = 0x00;
}


void __attribute__((constructor)) 
uart_constructor(void) {
  uart_init(UART_BAUD_SELECT(UART_BAUD_RATE,XTAL));
  fdevopen(uart_fdev, 0);
}


int
main(void)
{
  unsigned int input;


  eeprom_init();

  sei();

  portmap_init();
  init_ports();
  time_init();

  puts("\r\n welcome to the atmel board!\r\n\r\n");

  timeswitch_init();
  //  timeswitch_set(0, time_from_hms(0,0,3), time_from_hms(0,0,5), OUTPUT_L1, 1);
  //  timeswitch_set(1, time_from_hms(0,1,3), time_from_hms(0,1,5), OUTPUT_L1, 1);

  i2c_init();
  ds1307_init();
  tmp101_init(TMP101_ID);
  commandline_init();

  _delay_ms(100);

  for(;;) {

	input = uart_getc();

	if ( input != UART_NO_DATA ) {
	  commandline_addchar(input & 0xff);
	}

	if ( time_updated() ) { 

	  temp = tmp101_gettemp(TMP101_ID);
	  timeswitch_check(time_now());

	}
  }
						
}



