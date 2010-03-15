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

enum {
  OUTPUT_FIRST,
  OUTPUT_L1 = OUTPUT_FIRST,
  OUTPUT_L2,
  OUTPUT_FOGGER,
  OUTPUT_HEATING_WIRE,
  OUTPUT_HEATING_LAMP,
  OUTPUT_LAST
};


// maximum length of controller title
#define CONTROLER_TITLE_LEN 9

// some debug statements
//#define INIT_DEBUG
//#define COMMANDLINE_DEBUG
//#define PORTMAP_DEBUG



typedef unsigned char bool;
typedef uint32_t time_t;
typedef uint32_t date_t;
typedef uint8_t  pin_t;
typedef volatile uint8_t* port_t;


// these variables constitute the status and the setup of the
// controller. some are also persisted into eeprom, see
// eeprom.h/eeprom.c for initialization.
extern uint8_t temp;
extern uint8_t temp_setpoint[2];
extern uint8_t humidity;
extern uint8_t humidity_setpoint[2];
extern time_t  daytime[2];
extern date_t  wintertime[2];
extern char* controller_title[CONTROLER_TITLE_LEN];

// which outputs are currently switched on? a bit-mask.
extern uint8_t output_values;


struct port_pin_t {
  uint8_t po:4;
  uint8_t pi:4;
};




#ifndef INIT_DEBUG
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
#include "pcf8574a.h"

/*  LocalWords:  eeprom
 */
