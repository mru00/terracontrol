/* 
 * terrarium control
 * mru, november 2009
 *
 */

#include <stdio.h>
#include <util/twi.h>

#include "common.h"

// .aaa 1110 = 0x0e
#define PCF8574A_ADDRESS 0x38


extern void pcf8574a_init(void) {
  LOG_INIT();

  LOG_INIT_EXIT();
}


extern void pcf8574a_set(uint8_t value) {
  i2c_c_write_start(PCF8574A_ADDRESS);
  i2c_c_write_last (value);
}


