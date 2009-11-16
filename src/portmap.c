/* 
 * terrarium control
 * mru, november 2009
 *
 * portmap
 *
 */

#include <avr/io.h>

#include "common.h"

#define NULL ((void*)(0))


port_t portmap[4];

void portmap_init(void) {

  portmap[0] = NULL;
  portmap[1] = &PORTB;
  portmap[2] = &PORTC;
  portmap[3] = &PORTD;
}
