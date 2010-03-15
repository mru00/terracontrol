/* 
 * terrarium control
 * mru, november 2009
 *
 * portmap, provides indirection to ports with port id's 
 *
 */

#include <avr/io.h>
#include <stdio.h>
#include <avr/pgmspace.h>

#include "common.h"

#define PORTMAP_NAME(o) case o: uart_puts_P( #o ); break

void portmap_init(void) {
  LOG_INIT();

  LOG_INIT_EXIT();
}


void portmap_print_output(uint8_t output) {
  switch(output) {
  case OUTPUT_L1:           uart_puts_P("Lampe1"); break;
  case OUTPUT_L2:           uart_puts_P("Lampe2"); break;
  case OUTPUT_FOGGER:       uart_puts_P("Nebler"); break;
  case OUTPUT_HEATING_WIRE: uart_puts_P("HeizDraht"); break;
  case OUTPUT_HEATING_LAMP: uart_puts_P("HeizLampe"); break;
#ifdef PORTMAP_DEBUG
  default: 
	uart_puts_P("wrong output number" NEWLINE);
#endif
  }
}
