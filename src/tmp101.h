/* 
 * terrarium control
 * mru, november 2009
 *
 *
 * uses:
 *
 *  - module i2c
 *
 */



#pragma once


// .100 1xxx
#define TMP101_BASE_ADRESS 0x48

extern void tmp101_init(uint8_t id);

// returns the temperatur, in deg Celcius
extern uint8_t tmp101_gettemp(uint8_t id);




