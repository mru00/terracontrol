/* 
 * terrarium control
 * mru, november 2009
 *
 * portmap, provides indirection to ports with port id's 
 *
 */

#include <avr/io.h>
#include <stdio.h>

#include "common.h"

#define PORTMAP_NAME(o) case o: uart_puts( #o ); break

void portmap_init(void) {
  LOG_INIT();

  // setup ports
  DDRB |= (_BV(PB1) | 
		   _BV(PB2) | 
		   _BV(PB3) | 
		   _BV(PB4) | 
		   _BV(PB5));

  // set outputs off
  PORTB &= ~ (_BV(PB1) |
			  _BV(PB2) |
			  _BV(PB3) |
			  _BV(PB4) |
			  _BV(PB5));

  LOG_INIT_EXIT();
}

void portmap_setpin(uint8_t value, uint8_t output) {

  port_t port;
  uint8_t pin;

  switch(output) {
  case OUTPUT_L1:            port = &PORTB; pin = PB5; break;
  case OUTPUT_L2:            port = &PORTB; pin = PB4; break;
  case OUTPUT_FOGGER:        port = &PORTB; pin = PB3; break;
  case OUTPUT_HEATING_WIRE:  port = &PORTB; pin = PB2; break;
  case OUTPUT_HEATING_LAMP:  port = &PORTB; pin = PB1; break;

#ifdef PORTMAP_DEBUG
  default: 
	uart_puts("wrong output number" NEWLINE);
#endif
return;
  }

  if ( value )  *port |= _BV(pin);
  else *port &= ~_BV(pin);
}


void portmap_print_output(uint8_t output) {
  switch(output) {
	PORTMAP_NAME(OUTPUT_L1);
	PORTMAP_NAME(OUTPUT_L2);
	PORTMAP_NAME(OUTPUT_FOGGER);
	PORTMAP_NAME(OUTPUT_HEATING_WIRE);
	PORTMAP_NAME(OUTPUT_HEATING_LAMP);
#ifdef PORTMAP_DEBUG
  default: 
	uart_puts("wrong output number" NEWLINE);
#endif
  }
}
