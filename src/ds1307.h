/* 
 * terrarium control
 * mru, november 2009
 *
 *
 * uses:
 *
 * - module i2c
 */


#pragma once


extern void ds1307_init(void);
extern void ds1307_setdate(uint8_t y, uint8_t m, uint8_t d);
extern void ds1307_settime(uint8_t h, uint8_t m, uint8_t s);

extern time_t ds1307_gettime(void);

