/* 
 * terrarium control
 * mru, november 2009
 *
 * portmap
 *
 */


#pragma once

#define PORTMAP_DEBUG

enum {
  OUTPUT_FIRST,
  OUTPUT_L1 = OUTPUT_FIRST,
  OUTPUT_L2,
  OUTPUT_FOGGER,
  OUTPUT_HEATING_WIRE,
  OUTPUT_HEATING_LAMP,
  OUTPUT_LAST
};


struct output_set_t {
  uint8_t output : OUTPUT_LAST;
};


extern void portmap_init(void);
extern void portmap_setpin(uint8_t value, uint8_t output);
extern void portmap_print_output(uint8_t id);

// some inliners

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
