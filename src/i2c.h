/* 
 * terrarium control
 * mru, november 2009
 *
 *
 * please note that the only difference between write_w and write_r are
 * the different expected states, which are only checked if I2C_DEBUG is set.
 *
 * uses :
 *
 *  - TWI hardware
 *  - PORTC/PC5
 *  - PORTC/PC4
 */


#pragma once


// uncomment to enable debug output
//#define I2C_DEBUG

#define I2C_USE_INTERNAL_PULLUP



extern void i2c_init(void);
extern void i2c_start(void);
extern void i2c_stop(void);

// write address for read intent
extern void i2c_address_r( uint8_t addr );

// write address for write intent
extern void i2c_address_w( uint8_t addr );

// write a byte, write intent
extern void i2c_write_w( uint8_t );

// write a byte, read intent
extern void i2c_write_r( uint8_t );

// read a byte, send ACK
extern uint8_t i2c_read_ack(void);

// read a byte, no ACK
extern uint8_t i2c_read_nack(void);



// convenience functions declared inline:

inline void i2c_c_read_start(uint8_t address) {
  i2c_start();
  i2c_address_r( address );
}

inline void i2c_c_read_start_reg(uint8_t address, uint8_t reg){
  i2c_start();
  i2c_address_w( address );
  i2c_write_w ( reg );
  i2c_stop();
  i2c_start();
  i2c_address_r( address );
}

inline uint8_t i2c_c_read_next(void) {
  return i2c_read_ack();
}

inline uint8_t i2c_c_read_last(void) {
  uint8_t v =  i2c_read_nack();
  i2c_stop();
  return v;
}

inline void i2c_c_write_start(uint8_t address) {
  i2c_start();
  i2c_address_w( address );
}

inline void i2c_c_write_start_reg(uint8_t address, uint8_t reg) {
  i2c_start();
  i2c_address_w( address );
  i2c_write_w ( reg );  
}

inline void i2c_c_write_next(uint8_t data) {
  i2c_write_w ( data );
}

inline void i2c_c_write_last(uint8_t data) {
  i2c_write_w ( data );
  i2c_stop();
}
