/* 
 * terrarium control
 * mru, november 2009
 *
 *
 * common include stuff, very fragile
 *
 */

#pragma once

// index in daytime-arrays
enum {
  NIGHT,
  DAY
};

enum {
  DAYTIME_BEGIN,
  DAYTIME_END
};

typedef unsigned char bool;
typedef uint32_t time_t;
typedef uint8_t pin_t;
typedef volatile uint8_t* port_t;

extern volatile uint8_t temp;
extern volatile uint8_t temp_setpoint[2];
extern volatile uint8_t humidity;
extern volatile uint8_t humidity_setpoint[2];
extern volatile time_t daytime[2];


struct port_pin_t {
  uint8_t po:4;
  uint8_t pi:4;
};


static inline uint8_t __attribute__((pure))
is_digit (char d) {
  return d >= '0' && d <= '9';
}

static inline uint8_t __attribute__((pure))
is_number(char* s) {
  do {
	if ( !is_digit(*s) )  return 0;
	s++;
  } while ( *s != '\0');
  return 1;
}

// itoa for uint8
extern char* itoa8(uint8_t value, char* buf);

// itoa for time parts (h, m or s)
extern char* itoat(uint8_t value, char* buf);

uint8_t __attribute__((pure)) atoi8(char* buf);

#if 0
#  define LOG_INIT()
#else
#  define LOG_INIT() uart_puts ( " init: " __FILE__ NEWLINE )
#endif

#define NEWLINE "\r\n"


#ifndef NULL
#  define NULL ((void*)(0))
#endif

#define nop() do { asm volatile("nop"); } while (0)

// include everything from here for simplicity
#include "uart.h"
#include "time.h"
#include "i2c.h"
#include "timeswitch.h"
//#include "tlv5620.h"
#include "portmap.h"
#include "tmp101.h"
#include "ds1307.h"
#include "commandline.h"
#include "eeprom.h"
#include "version.h"
#include "hd4478.h"
#include "selftest.h"
