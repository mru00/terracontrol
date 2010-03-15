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

  LOG_INIT();


  for ( i = 0; i < OUTPUT_LAST; i ++ ) {

	itoa8(i+1, buf);
	hd4478_moveto(1, 0);
	hd4478_puts("POST ");
	hd4478_puts(buf);

#if 0
	uart_puts("SELFTEST ");
	uart_puts(buf);
	uart_puts(NEWLINE);
#endif

	portmap_setpin(1, i);

	_delay_ms(500);

	portmap_setpin(0, i);
	
	_delay_ms(500);
  }

  hd4478_clear();

  LOG_INIT_EXIT();
}

