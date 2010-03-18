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
 * Dallas DS1307
 * 64 x 8, Serial, I2C Real-Time Clock
 *
 * uses:
 *
 * - module i2c
 */

#pragma once

extern void ds1307_init(void);

extern void ds1307_setdate(const uint8_t y, const uint8_t m, const uint8_t d);
extern date_t ds1307_getdate(void);

extern void ds1307_settime(const uint8_t h, const uint8_t m, const uint8_t s);
extern time_t ds1307_gettime(void);
