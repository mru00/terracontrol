/* 
 * terrarium control
 * mru, november 2009
 *
 * TLV5620 8bit serial D/A converter
 *
 * timing tested with 11.0592 MHz, 
 * more nop()'s might be necessary for higher F_OSC
 */

#include <avr/io.h>
#include <avr/eeprom.h>
#include <stdio.h>
#include "common.h"


struct tlv5620_port_t {
  struct port_pin_t load;
  struct port_pin_t clk;
  struct port_pin_t data;

#ifdef TLV_USE_LDAC
  struct port_pin_t ldac;
#endif
};

static struct tlv5620_port_t tlv_ports;

static inline void write_tlv(const uint8_t x) {
  setpin(tlv_ports.clk);
  xpin (x, tlv_ports.data);
  nop();
  clearpin(tlv_ports.clk);
  nop();
}

void tlv_init(void) {
  LOG_INIT();
  LOG_INIT_EXIT();

}


void tlv_setup_port(const uint8_t po_load, const uint8_t pi_load, 
					const uint8_t po_clk, const uint8_t pi_clk,
					const uint8_t po_data, const uint8_t pi_data,
					const uint8_t po_ldac, const uint8_t pi_ldac) {

  tlv_ports.load.po = po_load;
  tlv_ports.load.pi = pi_load;

  tlv_ports.clk.po = po_clk;
  tlv_ports.clk.pi = pi_clk;

  tlv_ports.data.po = po_data;
  tlv_ports.data.pi = pi_data;

#ifdef TLV_USE_LDAC
  tlv_ports.ldac.po = po_ldac;
  tlv_ports.ldac.pi = pi_ldac;
#endif
}


void tlv_set(const uint8_t id, const uint8_t value) {


  // setup ldac & load

  setpin( tlv_ports.clk );
  setpin( tlv_ports.load );

#ifdef TLV_USE_LDAC
  clearpin( tlv_ports.ldac );
#endif

  // address
  write_tlv( id & _BV(1) );
  write_tlv( id & _BV(0) );

  // rng
  write_tlv( 0 );

  // value
  write_tlv( value & ( 1 << 7 ) );
  write_tlv( value & ( 1 << 6 ) );
  write_tlv( value & ( 1 << 5 ) );
  write_tlv( value & ( 1 << 4 ) );
  write_tlv( value & ( 1 << 3 ) );
  write_tlv( value & ( 1 << 2 ) );
  write_tlv( value & ( 1 << 1 ) );
  write_tlv( value & ( 1 << 0 ) );

  // strobe load & ldac
  clearpin( tlv_ports.load );
  nop();  
  setpin( tlv_ports.load );

#ifdef TLV_USE_LDAC
  nop();  nop();
  clearpin( tlv_ports.ldac );
  nop();  nop();
  setpin( tlv_ports.ldac );
#endif
}
