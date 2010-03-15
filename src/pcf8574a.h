/* 
 * terrarium control
 * mru, november 2009
 *
 * Texas Instruments 
 * REMOTE 8-BIT I/O EXPANDER FOR I2C BUS
 * 
 * uses:
 *
 * - module i2c
 */


#pragma once

extern void pcf8574a_init(void);
extern void pcf8574a_set(uint8_t value);
