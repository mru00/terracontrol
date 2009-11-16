/* 
 * terrarium control
 * mru, november 2009
 *
 *
 * please note that the only difference between write_w and write_r are
 * the different expected states, which are only checked if I2C_DEBUG is set.
 */


#pragma once


// uncomment to enable debug output
//#define I2C_DEBUG



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




// conveniece

// start, address_w, write_w, stop


extern void i2c_c_read_start(uint8_t address, uint8_t reg);
extern uint8_t i2c_c_read_next(void);
extern uint8_t i2c_c_read_last(void);

extern void i2c_c_write_start(uint8_t address);
extern void i2c_c_write_next(uint8_t data);
extern void i2c_c_write_last(uint8_t data);
