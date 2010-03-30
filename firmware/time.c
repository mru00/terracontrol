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


#include <avr/interrupt.h>

#include "common.h"

date_t current_date;
time_t current_time;
static uint8_t volatile newtime;

ISR(INT0_vect) {
  newtime++;
}

void time_init(void) {

  LOG_INIT();

  DDRD &= ~_BV(PD2);

  // internal pullup seems NOT to work 
  //  PORTD |= _BV(PD2);

  PORTD &= ~_BV(PD2);

  // The rising edge of INT0 generates an interrupt request.  
  // enable external interrupt 0

  MCUCR |= _BV(ISC01) | _BV(ISC00);
  GICR  |= _BV(INT0);                   

  newtime = 0;

  LOG_INIT_EXIT();
}


bool time_updated(void) {
  if ( newtime  ) {

	current_time = ds1307_gettime();
	current_date = ds1307_getdate();

	newtime --;
	return 1;
  }
  return 0;
}


#ifdef TIME_STRUCT
#  define EQ(t1,t2) (t1.h == t2.h && t1.m == t2.m && t1.s == t2.s)
#  define LT(t1,t2) (t1.h < t2.h || t1.m < t2.m || t1.s < t2.s )
#  define LE(t1,t2) (t1.h <= t2.h || t1.m <= t2.m || t1.s <= t2.s )
#else
#  define EQ(t1,t2) (t1 == t2)
#  define LT(t1,t2) (t1 < t2)
#  define LE(t1,t2) (t1 <= t2)
#endif

#define GE(t1,t2) !LT(t1, t2)


uint8_t time_in_range(const time_t begin, const time_t end) {
  if ( EQ(begin,end) ) return 0;
  if ( LT(begin,end) ) return GE(current_time,begin) && LE(current_time,end);
  return GE(current_time,begin)  || LE(current_time,end);
}


char* ttoa(const time_t time, char* buf) {
  itoat(time_get_h(time), buf+0);
  itoat(time_get_m(time), buf+3);
  itoat(time_get_s(time), buf+6);
  buf[2] = ':';
  buf[5] = ':';
  return buf;
}

void date_print(const date_t date) {
  char buf[4];
  uart_puts(itoat(date_get_d(date), buf));
  uart_putc('.');
  uart_puts(itoat(date_get_m(date), buf));
  uart_putc('.');
  uart_puts(itoat(date_get_y(date), buf));
}
