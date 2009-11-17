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


port_t portmap[nPORTLAST];
port_t ddrmap[nPORTLAST];
port_t pinmap[nPORTLAST];


void portmap_init(void) {

  LOG_INIT();

  portmap[nPORTB] = &PORTB;
  portmap[nPORTC] = &PORTC;
  portmap[nPORTD] = &PORTD;

  ddrmap[nPORTB] = &DDRB;
  ddrmap[nPORTC] = &DDRC;
  ddrmap[nPORTD] = &DDRD;


  pinmap[nPORTB] = &PINB;
  pinmap[nPORTC] = &PINC;
  pinmap[nPORTD] = &PIND;

}
