/************************************************************************
 * This file is part of TerraControl.								    *
 * 																	    *
 * TerraControl is free software; you can redistribute it and/or modify *
 * it under the terms of the GNU General Public License as published    *
 * by the Free Software Foundation; either version 2 of the License, or *
 * (at your option) any later version.								    *
 * 																	    *
 * TerraControl is distributed in the hope that it will be useful,	    *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of	    *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the	    *
 * GNU General Public License for more details.						    *
 * 																	    *
 * You should have received a copy of the GNU General Public License    *
 * along with TerraControl; if not, write to the Free Software		    *
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 *
 * USA																    *
 * Written and (c) by mru											    *
 * Contact <mru@fourier> for comment & bug reports					    *
 ************************************************************************/

#include <avr/io.h>
#include <util/delay.h>

#include "common.h"

void selftest_perform(void) {

  uint8_t i;
  char buf[4];

  LOG_INIT();

#ifdef HD4478_DEBUG
  uint8_t j;
  for ( i = 0; i < 16; i ++ ) {
	hd4478_moveto(0, 0); for ( j=0; j<8; j++ ) hd4478_putc(i*16 + j);
	hd4478_moveto(1, 0); for ( j=0; j<8; j++ ) hd4478_putc(i*16 + 8+j);
	_delay_ms(1000);
  }
#endif

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

	pcf8574a_set(i);

	_delay_ms(500);

	//	portmap_setpin(0, i);
	
	//	_delay_ms(500);
  }

  LOG_INIT_EXIT();
}

