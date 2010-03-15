/* 
 * terrarium control
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
