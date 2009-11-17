/* 
 * terrarium control
 * mru, november 2009
 *
 * portmap
 *
 */


#pragma once


// port numbers
enum {
  nPORTB,
  nPORTC,
  nPORTD,
  nPORTLAST
};


struct io_map_t {
  struct port_pin_t portpin;
  char name[7];
};

extern port_t portmap[];
extern port_t ddrmap[];
extern port_t pinmap[];


extern void portmap_init(void);


// some inliners


inline void setpin(struct port_pin_t pin) {
  *portmap[pin.po] |= (1 << pin.pi);
}

inline void setpin2(uint8_t port, uint8_t pin) {
  *portmap[port] |= (1 << pin);
}

inline void clearpin(struct port_pin_t pin) { 
  *portmap[pin.po] &= ~(1 << pin.pi);
}

inline void clearpin2(uint8_t port, uint8_t pin) {
  *portmap[port] &= ~(1 << pin);
}

inline void xpin(uint8_t x, struct port_pin_t pin) {
  if ( x ) setpin(pin);
  else {clearpin(pin);} 
}

inline void xpin2( uint8_t x, uint8_t port, uint8_t pin) { 
  if ( x ) setpin2(port,pin);
  else clearpin2(port,pin);
}

inline void setup_as_input2(uint8_t port, uint8_t pin) {
  *ddrmap[port] &= ~_BV(pin);
}

inline void setup_as_output2(uint8_t port, uint8_t pin) {
  *ddrmap[port] |= _BV(pin);
}

inline void setup_as_output(struct port_pin_t po) {
  *ddrmap[po.po] |= _BV(po.pi);
}
