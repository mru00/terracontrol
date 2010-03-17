/* 
 * terrarium control
 * mru, november 2009
 *
 */


#pragma once

#include <avr/eeprom.h>

extern uint8_t ee_tempsetpoint[2] EEMEM;
extern uint8_t ee_humiditysetpoint[2] EEMEM;
extern time_t ee_daytime[2] EEMEM;
extern char ee_controller_title[CONTROLER_TITLE_LEN] EEMEM;

extern struct timeswitch_t ee_timeswitches[N_TIMESWITCHES] EEMEM;
extern uint8_t ee_wdt_reset_count EEMEM;



// initializes all ram values from eeprom
extern void eeprom_init(void);
extern void eeprom_increate_wdt_reset(void);
