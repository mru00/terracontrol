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
/* 
 * functions to control the timeswitches
 *
 */


#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <stdio.h>

#include "common.h"


void timeswitch_init(void) {
  LOG_INIT();
  LOG_INIT_EXIT();
}

void timeswitch_check() {
  
  uint8_t i;
  output_values = 0;

  for ( i = 0; i < N_TIMESWITCHES; i ++ ) {
	if ( ! timeswitch_active(i) ) continue;

	output_values |= _BV(settings.timeswitches[i].output & ~OUTPUT_ENABLED_MASK);
  }
}


void timeswitch_set(const uint8_t id, 
					const time_t on, 
					const time_t off, 
					const uint8_t output, 
					const uint8_t enabled) {

#ifdef TIMESWITCH_DEBUG
  if ( id < 0 || id >= N_TIMESWITCHES ) {
	uart_puts_P("illegal timeswitch id" NEWLINE);
  }
#endif

  settings.timeswitches[id].on = on;
  settings.timeswitches[id].off = off;
  settings.timeswitches[id].output = output | (enabled ? OUTPUT_ENABLED_MASK : 0);

}

