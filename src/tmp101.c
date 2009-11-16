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

  puts("asdf");

  // write configuration
  i2c_start();
  i2c_address_w( TMP101_BASE_ADRESS + id );
  i2c_write_w( TR_CONF );
  i2c_write_w( _BV(TC_R0) | _BV(TC_R1) );
  i2c_stop();


  // select temperature register

  i2c_start();
  i2c_address_w(  TMP101_BASE_ADRESS | id );
  i2c_write_w( TR_TEMP );
  i2c_stop();  
}


uint8_t tmp101_gettemp(uint8_t id) {


  uint8_t t1;

  i2c_start();
  i2c_address_r(  TMP101_BASE_ADRESS | id );
  t1 = i2c_read_nack();

  // we only read the first byte
  // we don't generate an ACK
  // we simply stop, should suffice

  i2c_stop();

  return t1;
}


