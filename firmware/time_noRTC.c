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
 * RTC without RTC...
 *
 */


#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <avr/wdt.h>
#include <util/delay.h>

#include <stdio.h>

#include "common.h"


#define DEBOUNCE    256L        // debounce clock (256Hz = 4msec)

time_t volatile current_time;

static uint8_t volatile newtime;
static uint8_t prescaler;


SIGNAL (SIG_OUTPUT_COMPARE1A)
{
		 
#if F_OSC % DEBOUNCE                     // bei rest
  OCR1A = F_OSC / DEBOUNCE - 1;      // compare DEBOUNCE - 1 times
#endif

  if( --prescaler == 0 ) {
    prescaler = (uchar)DEBOUNCE;

	if ( ++current_time == SECONDS_PER_DAY )
	  current_time = 0;

	newtime = 1;

#if F_OSC % DEBOUNCE         // handle remainder
    OCR1A = F_OSC / DEBOUNCE + F_OSC % DEBOUNCE - 1; // compare once per second
#endif

  }
}


void time_init(void) {

  TCCR1B = 1 << WGM12^1 << CS10;		// divide by 1, clear on compare
  OCR1A = XTAL / DEBOUNCE - 1;
  TCNT1 = 0;

  current_time = 0;
  newtime = 0;

  prescaler = (uchar)DEBOUNCE;
  TIMSK = 1 << OCIE1A;
}


void time_current_print(void) {
  time_print(current_time);
}

void time_print(time_t t) {
  uint8_t h = t / 3600;
  uint8_t m = t / 60 - h*60;
  uint8_t s = t  - (h*3600 + m*60);
  printf("%02d:%02d:%02d", h, m, s);
}



bool time_updated(void) {
  if ( newtime ) {
	newtime = 0;
	return 1;
  }
  return 0;
}


time_t const  time_now(void) {
  return current_time;
}

