/* 
 * terrarium control
 * mru, november 2009
 *
 */

#include <avr/io.h>
#include <util/delay.h>

#include "common.h"

void selftest_perform(void) {

  uint8_t i;
  char buf[4];


  for ( i = 0; i < OUTPUT_LAST; i ++ ) {

	hd4478_clear();
	hd4478_puts("SELFTEST ");
	hd4478_puts(itoa8(i, buf));

	uart_puts("SELFTEST ");
	uart_puts(itoa8(i, buf));
	uart_puts(NEWLINE);

	portmap_setpin(1, i);

	_delay_ms(500);

	portmap_setpin(0, i);
	
	_delay_ms(500);
  }

  hd4478_clear();
}

