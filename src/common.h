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


#define CONTROLER_TITLE_LEN 20

typedef unsigned char bool;
typedef uint32_t time_t;
typedef uint32_t date_t;
typedef uint8_t pin_t;
typedef volatile uint8_t* port_t;

extern uint8_t temp;
extern uint8_t temp_setpoint[2];
extern uint8_t humidity;
extern uint8_t humidity_setpoint[2];
extern time_t daytime[2];
extern date_t wintertime[2];


struct port_pin_t {
  uint8_t po:4;
  uint8_t pi:4;
};




#if 0
#  define LOG_INIT()
#  define LOG_INIT_EXIT()
#else
#  define LOG_INIT() uart_puts ( "<" __FILE__  )
#  define LOG_INIT_EXIT() uart_puts ( ">" NEWLINE )
#endif


#define NEWLINE "\r\n"


#ifndef NULL
#  define NULL ((void*)(0))
#endif

#define nop() do { asm volatile("nop"); } while (0)

// include everything from here for simplicity
#include "itoa.h"
#include "uart.h"
#include "time.h"
#include "i2c.h"
#include "timeswitch.h"
//#include "tlv5620.h"
#include "portmap.h"
#include "tmp101.h"
#include "ds1307.h"
#include "commandline.h"
#include "version.h"
#include "hd4478.h"
#include "selftest.h"
#include "eeprom.h"
#include "sht11.h"
