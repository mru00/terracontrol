 /* 
 * terrarium control
 * mru, november 2009
 *
 * http://www.mikrocontroller.net/topic/61179
 *
 */

#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/twi.h>

#include <stdio.h>


#include "common.h"

enum {
  TC_SD,         // shutdown
  TC_TM,         // thermostat mode
  TC_POL,        // polarity
  TC_F0,         // fault queue
  TC_F1,
  TC_R0,         // converter resolution
  TC_R1,
  TC_OA          // os/alert
};

enum {
  TR_TEMP,      // temperature register
  TR_CONF,      // configuration register
  TR_TLOW,      // T_Low register
  TR_THIGH      // T_High register
};


void tmp101_init(uint8_t id) {

  LOG_INIT();

  // write configuration
  i2c_c_write_start_reg(TMP101_BASE_ADRESS + id, TR_CONF);
  i2c_c_write_last( _BV(TC_R0) | _BV(TC_R1) );

  // select temperature register

  i2c_c_write_start(TMP101_BASE_ADRESS + id);
  i2c_c_write_last( TR_TEMP );

  LOG_INIT_EXIT();
}


uint8_t tmp101_gettemp(uint8_t id) {
  i2c_c_read_start(TMP101_BASE_ADRESS + id);
  return i2c_c_read_last();
}


