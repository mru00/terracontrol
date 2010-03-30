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
 * http://www.mikrocontroller.net/topic/61179
 *
 */

#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/twi.h>

#include <stdio.h>


#include "common.h"


#ifdef TMP101_DUMMY
#  warning TMP101 in dummy mode
#endif


enum {
  TC_SD,         // shutdown
  TC_TM,         // thermostat mode
  TC_POL,        // polarity
  TC_F0,         // fault queue
  TC_F1,
  TC_R0,         // converter resolution
  TC_R1,
  TC_OA          // os/alert
};

enum {
  TR_TEMP,      // temperature register
  TR_CONF,      // configuration register
  TR_TLOW,      // T_Low register
  TR_THIGH      // T_High register
};


void tmp101_init(uint8_t id) {

  LOG_INIT();

#ifndef TMP101_DUMMY

  // write configuration
  i2c_c_write_start_reg(TMP101_BASE_ADRESS + id, TR_CONF);
  i2c_c_write_last( _BV(TC_R0) | _BV(TC_R1) );

  // select temperature register

  i2c_c_write_start(TMP101_BASE_ADRESS + id);
  i2c_c_write_last( TR_TEMP );

#endif

  LOG_INIT_EXIT();
}


uint8_t tmp101_gettemp(uint8_t id) {
#ifdef TMP101_DUMMY
  return 42;
#else
  i2c_c_read_start(TMP101_BASE_ADRESS + id);
  return i2c_c_read_last();
#endif
}


