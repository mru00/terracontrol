/* 
 * terrarium control
 * mru, november 2009
 *
 * portmap
 *
 */


#pragma once

#include <avr/io.h>


extern void portmap_init(void);
extern void portmap_print_output(uint8_t id);

// some inliners

static const port_t PORTS[] = {  NULL, &PORTB, &PORTC, &PORTD };
static const port_t PINS[] = {  NULL, &PINB, &PINC, &PIND };
static const port_t DDRS[] = {  NULL, &DDRB, &DDRC, &DDRD };


inline void setpin2(port_t port, uint8_t pin) {
  *port |= _BV(pin);
}

inline void clearpin2(port_t port, uint8_t pin) {
  *port &= ~_BV(pin);
}

inline void xpin2( uint8_t x, port_t port, uint8_t pin) { 
  if ( x ) setpin2(port,pin);
  else clearpin2(port,pin);
}



static inline void setpin3(uint8_t port, uint8_t pin) {
  *PORTS[port] |= _BV(pin);
}

static inline uint8_t getpin3(uint8_t port, uint8_t pin) {
  return (*PINS[port] & _BV(pin)) != 0;
}

static inline void clearpin3(uint8_t port, uint8_t pin) {
  *PORTS[port] &= ~_BV(pin);
}

static inline void xpin3( uint8_t x, uint8_t port, uint8_t pin) { 
  if ( x ) setpin3(port,pin);
  else clearpin3(port,pin);
}

static inline void io_output3( uint8_t port, uint8_t pin) {
  *DDRS[port] |= _BV(pin);
}

static inline void io_input_pullup3( uint8_t port, uint8_t pin) {
  *PORTS[port] |= _BV(pin);
  *DDRS[port] &= ~_BV(pin);
}

static inline void io_input_no_pullup3( uint8_t port, uint8_t pin) {
  *PORTS[port] &= ~_BV(pin);
  *DDRS[port] &= ~_BV(pin);
}

static inline void io_input_dc_pullup3( uint8_t port, uint8_t pin) {
  *DDRS[port] &= ~_BV(pin);
}
