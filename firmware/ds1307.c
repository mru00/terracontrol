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
 * Contact <mru@sisyphus.teil.cc> for comment & bug reports				*
 ************************************************************************/
/* 
 * mru, november 2009
 *
 */

#include <stdio.h>
#include <util/twi.h>

#include "common.h"

// .110 1000 = 0x68
#define DS1307_ADDRESS 0x68


#ifdef DS1307_DUMMY
#  warning DS1307 in dummy mode
#endif


// DS1307 registers
enum {
  DR_SECONDS,
  DR_MINUTES,
  DR_HOURS,
  DR_DAY,              // weekday
  DR_DATE,
  DR_MONTH,
  DR_YEAR,
  DR_CONTROL,
  DR_RAM,
};

enum {
  DC_CH = 7   // clock halt in CR_SECONDS
};


// DS1307 Control register bits
enum {
  DC_RS0,   // 
  DC_RS1,   // rate select
  DC_NA1,
  DC_NA2,
  DC_SQWE,  // square-wave enable
  DC_NA3,
  DC_NA4,
  DC_OUT    // output control
};

static uint8_t __attribute__((pure))
to_bcd(const uint8_t val) {
  uint8_t hi = (val / 10) & 0xf;
  uint8_t lo = (val - hi*10) & 0xf;
  return (hi<<4) + lo;
}

static uint8_t __attribute__((pure))
from_bcd(const uint8_t val) {
  return ( (val & 0xf0) >> 4 )*10 + (val & 0x0f);
}

void ds1307_init(void) {

  LOG_INIT();

#ifndef DS1307_DUMMY
  uint8_t t;

  i2c_c_read_start_reg(DS1307_ADDRESS, DR_SECONDS);
  t = i2c_c_read_last();

  // the clock was reset - reinitialize
  // we check if the clock was reset by testing the CH bit of the
  // time register
  if ( t & _BV(DC_CH) ) {
	i2c_c_write_start_reg(DS1307_ADDRESS, DR_SECONDS);
	i2c_c_write_next ( 0 ); // set CH to 0, start oscillator, set seconds to 0
	i2c_c_write_next ( 0 ); // set minutes to 0
	i2c_c_write_next ( 0 ); // set hours to 0
	i2c_c_write_next ( 0 ); // set day to 0
	i2c_c_write_next ( 1 ); // set date to 0
	i2c_c_write_next ( 1 ); // set month to 0
	i2c_c_write_next ( 9 ); // set year to 0
	i2c_c_write_last ( (1<<DC_SQWE)| // SquareWave enable
					   (0<<DC_RS0) | // rate select: 1Hz
					   (0<<DC_RS1) |
					   (0<<DC_OUT)); // normal output
  }

#endif
  LOG_INIT_EXIT();
}

void ds1307_setdate(uint8_t y, uint8_t m, uint8_t d) {

#ifndef DS1307_DUMMY
  i2c_c_write_start_reg(DS1307_ADDRESS, DR_DATE);
  i2c_c_write_next ( to_bcd(d) );
  i2c_c_write_next ( to_bcd(m) );
  i2c_c_write_last ( to_bcd(y) );
#endif
}


void ds1307_settime(uint8_t h, uint8_t m, uint8_t s) {
#ifndef DS1307_DUMMY

  i2c_c_write_start_reg(DS1307_ADDRESS, DR_SECONDS);
  i2c_c_write_next ( to_bcd(s) & 0x7f );
  i2c_c_write_next ( to_bcd(m) );
  i2c_c_write_last ( to_bcd(h)  );
#endif
}

time_t ds1307_gettime(void) {
#ifndef DS1307_DUMMY

  i2c_c_read_start_reg(DS1307_ADDRESS, DR_SECONDS);

  uint8_t s = from_bcd(i2c_c_read_next());
  uint8_t m = from_bcd(i2c_c_read_next());
  uint8_t h = from_bcd(i2c_c_read_last());

  return  time_from_hms(h, m, s);
#else
  return time_from_hms(1, 2, 3);
#endif
}

date_t ds1307_getdate(void) {
#ifndef DS1307_DUMMY

  i2c_c_read_start_reg(DS1307_ADDRESS, DR_DATE);

  uint8_t d = from_bcd(i2c_c_read_next());
  uint8_t m = from_bcd(i2c_c_read_next());
  uint8_t y = from_bcd(i2c_c_read_last());

  return  date_from_dmy(d, m, y);
#else
  return date_from_dmy(1, 2, 3);
#endif
}
