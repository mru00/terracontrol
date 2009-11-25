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


void portmap_init(void) {
  LOG_INIT();

  // setup ports
  DDRB |= _BV(PB1) | _BV(PB2) | _BV(PB3) | _BV(PB4) | _BV(PB5);
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

  default: 
#ifdef PORTMAP_DEBUG
	uart_puts("wrong output number" NEWLINE);
#endif
return;
  }

  if ( value )  *port |= _BV(pin);
  else *port &= ~_BV(pin);
}

