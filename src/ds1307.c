/* 
 * terrarium control
 * mru, november 2009
 *
 */

#include <stdio.h>
#include <util/twi.h>

#include "common.h"

// .110 1000 = 0x68
#define DS1307_ADDRESS 0x68


// DS1307 registers
enum {
  DR_SECONDS,
  DR_MINUTES,
  DR_HOURS,
  DR_DAY,              // weekday
  DR_DATE,
  DR_MONTH,
  DR_YEAR,
  DR_CONTROL,
  DR_RAM,
};

enum {
  DC_CH = 7   // clock halt in CR_SECONDS
};


// DS1307 Control register bits
enum {
  DC_RS0,   // 
  DC_RS1,   // rate select
  DC_NA1,
  DC_NA2,
  DC_SQWE,  // square-wave enable
  DC_NA3,
  DC_NA4,
  DC_OUT    // output control
};

static inline uint8_t __attribute__((pure))
to_bcd(const uint8_t val) {
  uint8_t hi = (val / 10) & 0xf;
  uint8_t lo = (val - hi*10) & 0xf;
  return (hi<<4) + lo;
}

static inline uint8_t __attribute__((pure))
from_bcd(const uint8_t val) {
  return ( (val & 0xf0) >> 4 )*10 + (val & 0x0f);
}

void ds1307_init(void) {

  LOG_INIT();

  uint8_t t;

  i2c_c_read_start_reg(DS1307_ADDRESS, DR_SECONDS);
  t = i2c_c_read_last();

  // the clock was reset - reinitialize
  if ( t & _BV(DC_CH) ) {
	i2c_c_write_start_reg(DS1307_ADDRESS, DR_SECONDS);
	i2c_c_write_next ( 0 ); // set CH to 0, start oscillator, set seconds to 0
	i2c_c_write_next ( 0 ); // set minutes to 0
	i2c_c_write_next ( 0 ); // set hours to 0
	i2c_c_write_next ( 0 ); // set day to 0
	i2c_c_write_next ( 0 ); // set date to 0
	i2c_c_write_next ( 0 ); // set month to 0
	i2c_c_write_next ( 0 ); // set year to 0
	i2c_c_write_last ( _BV(DC_SQWE)  ); // set SquareWave enable, rate select = 0 -> 1Hz
  }
}

void ds1307_setdate(uint8_t y, uint8_t m, uint8_t d) {

  i2c_c_write_start_reg(DS1307_ADDRESS, DR_DATE);
  i2c_c_write_next ( to_bcd(d) );
  i2c_c_write_next ( to_bcd(m) );
  i2c_c_write_last ( to_bcd(y) );

}


void ds1307_settime(uint8_t h, uint8_t m, uint8_t s) {

  i2c_c_write_start_reg(DS1307_ADDRESS, DR_SECONDS);
  i2c_c_write_next ( to_bcd(s) & 0x7f );
  i2c_c_write_next ( to_bcd(m) );
  i2c_c_write_last ( to_bcd(h)  );
}

time_t ds1307_gettime(void) {

  i2c_c_read_start_reg(DS1307_ADDRESS, DR_SECONDS);

  uint8_t s = from_bcd(i2c_c_read_next());
  uint8_t m = from_bcd(i2c_c_read_next());
  uint8_t h = from_bcd(i2c_c_read_last());

  return  time_from_hms(h, m, s);
}
