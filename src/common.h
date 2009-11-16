/* 
 * terrarium control
 * mru, november 2009
 *
 */


#pragma once

typedef unsigned char byte_t;
typedef unsigned char uchar;
typedef unsigned int uint;
typedef unsigned char bool;

typedef uint32_t time_t;

typedef volatile uint8_t* port_t;
typedef uint8_t pin_t;

struct port_pin_t {

  uint8_t po:4;
  uint8_t pi:4;
};



#define setpin(pin)   *(portmap[pin.po]) |= (1 << pin.pi);
#define setpin2(port, pin)   *(portmap[port]) |= (1 << pin);

#define clearpin(pin) *(portmap[pin.po]) &= ~(1 << pin.pi);
#define clearpin2(port, pin) *(portmap[port]) &= ~(1 << pin);

#define xpin(x, pin) do { if ( x ) {setpin(pin);} else {clearpin(pin);} } while (0)
#define xpin2(x, port,pin) do { if ( x ) {setpin2(port,pin);} else {clearpin2(port,pin);} } while (0)


#define nop() do { asm volatile("nop"); } while (0)



#include "time.h"
#include "uart.h"
#include "i2c.h"
#include "timeswitch.h"
#include "tlv5620.h"
#include "portmap.h"
#include "tmp101.h"
#include "ds1307.h"
