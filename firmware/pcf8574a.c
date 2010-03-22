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
 * written for PCF8574N
 */

#include <stdio.h>
#include <util/twi.h>

#include "common.h"

#ifdef PCF857A_DUMMY
#  warning PCF857A in dummy mode
#endif


#define PCF8574A_ADDRESS 0x38
#define PCF8574N_ADDRESS 0x20



extern void pcf8574a_init(void) {
  LOG_INIT();

  LOG_INIT_EXIT();
}


extern void pcf8574a_set(uint8_t value) {
#ifndef PCF8574A_DUMMY
  i2c_c_write_start(PCF8574N_ADDRESS);
  i2c_c_write_last (value);
#endif
}


