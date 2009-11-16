
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


#define TMP101_ID 1

int main(void)
{
  unsigned int input;
  uint8_t temp = 0;

  uart_init(UART_BAUD_SELECT(UART_BAUD_RATE,XTAL));
  fdevopen(uart_fdev, 0);

  portmap_init();
  init_ports();
  time_init();
  timeswitch_init();

  tlv_setup_port(nPORTD, PD6,   // LOAD
				 nPORTB, PB0,   // CLK
				 nPORTD, PD7,   // DATA
				 nPORTD, PD5);  // LDAC

  timeswitch_set(0, 12, 15, nPORTC, PC3);
  timeswitch_set(2, 3, 9, nPORTC, PC3);
  
  sei();

  puts("\r\n welcome to the atmel board!\r\n\r\n");

  i2c_init();
  ds1307_init();
  tmp101_init(TMP101_ID);

  _delay_ms(100);

  for(;;) {

	_delay_ms(5);

	input = uart_getc();

	if ( input != UART_NO_DATA ) {

	  uart_putc(input & 0xff);

	  if ( (input & 0xff) == '\r' ) {
		time_current_print();
		puts("\r\n");
	  }
	}

	if ( time_updated() ) { 

	  timeswitch_check(time_now());
	  temp = tmp101_gettemp(TMP101_ID);

	  printf("time: " TIME_PRINTF_MASK " temp: %d\r\n", TIME_PRINTF_DATA(current_time), temp);
	}
  }                                                       
}

