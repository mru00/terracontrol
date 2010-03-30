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
 * Written and (c) by mru, nov 2009 								    *
 * Contact <mru@sisyphus.teil.cc> for comment & bug reports				*
 ************************************************************************/


#include <avr/eeprom.h>
#include <stdio.h>
#include <string.h>

#include "common.h"

#define VALID_MASK 0xA5

uint8_t ee_valid_configuration EEMEM;
struct global_settings_t eeprom_settings EEMEM;
uint8_t settings_changed = 0;

void eeprom_init(void) {

  LOG_INIT();
  
  uint8_t i;

  // if the eeprom - data seems to be invalid, create a "safe" default
  // configuration
  if ( eeprom_read_byte(&ee_valid_configuration) != VALID_MASK) {

	settings.daytime[0] = time_from_hms(8, 0, 0);
	settings.daytime[1] = time_from_hms(20, 0, 0);

	settings.temp_setpoint[0] = 20;
	settings.temp_setpoint[1] = 25;

	settings.humidity_setpoint[0] = 50;
	settings.humidity_setpoint[1] = 55;

	settings.hyst_temp = 3;
	settings.hyst_humidity = 3;
	
	timeswitch_set(0, 
				   time_from_hms(11, 0, 0), 
				   time_from_hms(13, 0, 0), 
				   OUTPUT_L1, 
				   1);

	timeswitch_set(1, 
				   time_from_hms(10, 0, 0), 
				   time_from_hms(14, 0, 0), 
				   OUTPUT_L2, 
				   1);

	timeswitch_set(2, 
				   time_from_hms(10, 0, 0), 
				   time_from_hms(14, 0, 0), 
				   OUTPUT_HEATING_LAMP, 
				   1);

	for ( i = 3; i < N_TIMESWITCHES; i++ )
	  timeswitch_set(i, time_from_hms(0,0,0), time_from_hms(0,0,0), 0, 0);

	strncpy((char*)settings.controller_title, "NONAME", CONTROLER_TITLE_LEN);

	settings_changed = 1;
	eeprom_commit();

	return;
  }

  eeprom_read_block ((void *) &settings, 
					 (const void *) &eeprom_settings, 
					 sizeof(struct global_settings_t));

  LOG_INIT_EXIT();
}


void eeprom_increase_wdt_reset(void) {
  //  uint8_t wdt_count;
  //  wdt_count = eeprom_read_byte(&ee_wdt_reset_count);
  //  eeprom_write_byte(&ee_wdt_reset_count, wdt_count + 1);
}



void eeprom_commit(void) {

  //  if (!eeprom_is_ready()) return;

  //  if (settings_changed) {
	eeprom_write_block( (const void*) &settings, 
						&eeprom_settings, 
						sizeof(struct global_settings_t));
	eeprom_write_byte(&ee_valid_configuration, VALID_MASK);
	//	settings_changed = 0;
	//  }

}
