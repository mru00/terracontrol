
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



static struct port_pin_t __attribute__((pure))
portpin(const uint8_t port, const uint8_t pin) {
  struct port_pin_t t;
  t.po = port;
  t.pi = pin;
  return t;
}


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


void __attribute__((constructor)) 
uart_constructor(void) {
  uart_init(UART_BAUD_SELECT(UART_BAUD_RATE,XTAL));
  fdevopen(uart_fdev, 0);
}



int
main(void)
{
  unsigned int input;
  uint8_t temp = 0;


  sei();


  portmap_init();
  init_ports();
  time_init();


  puts("\r\n welcome to the atmel board!\r\n\r\n");

  timeswitch_init();
  timeswitch_set(0, 12, 15,   portpin(nPORTC, PC3));
  timeswitch_set(1, 100, 103, portpin(nPORTC, PC3));
  timeswitch_set(2, 70, 78,   portpin(nPORTC, PC3));
  timeswitch_set(3, 30, 35,   portpin(nPORTC, PC3));
  timeswitch_set(4, 22, 25,   portpin(nPORTC, PC3));
  timeswitch_set(5, 3, 9,     portpin(nPORTC, PC3));


  i2c_init();
  ds1307_init();
  tmp101_init(TMP101_ID);
  commandline_init();

  _delay_ms(100);

  for(;;) {

	input = uart_getc();

	if ( input != UART_NO_DATA ) {


	  if ( (input & 0xff) == '\r' ) {
		commandline_processline();
	  }
	  else {
		commandline_addchar(input & 0xff);
	  }
	}

	if ( time_updated() ) { 

	  timeswitch_check(time_now());
	  temp = tmp101_gettemp(TMP101_ID);

	  //	  printf("time: " TIME_PRINTF_MASK " temp: %dC\r\n", TIME_PRINTF_DATA(current_time), temp);

	}
  }

						
}



