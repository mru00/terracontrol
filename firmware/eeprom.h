/* 
 * terrarium control
 * mru, november 2009
 *
 */


#pragma once

#include <avr/eeprom.h>

extern uint8_t ee_wdt_reset_count EEMEM;
extern uint8_t settings_changed;


// initializes all ram values from eeprom
extern void eeprom_init(void);
extern void eeprom_increase_wdt_reset(void);
extern void eeprom_commit(void);
