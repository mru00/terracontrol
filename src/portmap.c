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


#ifndef NULL
#  define NULL ((void*)(0))
#endif



void portmap_init(void) {

  LOG_INIT();

  DDRC |= _BV(PC2);
}


void portmap_setpin(uint8_t value, uint8_t output) {

  port_t port;
  uint8_t pin;

  switch(output) {
  case OUTPUT_L1: port = &PORTC; pin = PC3; break;
  default: 
#ifdef PORTMAP_DEBUG
	puts("wrong output number");
#endif
return;
  }

  if ( value )  *port |= _BV(pin);
  else *port &= ~_BV(pin);

}

