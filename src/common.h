/* 
 * terrarium control
 * mru, november 2009
 *
 *
 * common include stuff, very fragile
 *
 */

#pragma once




typedef unsigned char bool;
typedef uint32_t time_t;
typedef uint8_t pin_t;
typedef volatile uint8_t* port_t;


struct port_pin_t {
  uint8_t po:4;
  uint8_t pi:4;
};


#if 1
#  define LOG_INIT()
#else
#  define LOG_INIT() puts ( " init: " __FILE__ )
#endif


#define nop() do { asm volatile("nop"); } while (0)

// include everything from here for simplicity
#include "time.h"
#include "uart.h"
#include "i2c.h"
#include "timeswitch.h"
#include "tlv5620.h"
#include "portmap.h"
#include "tmp101.h"
#include "ds1307.h"
#include "commandline.h"
