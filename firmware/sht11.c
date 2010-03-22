/*
 * terrarium control
 * mru, november 2009
 *
 */
#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>

#include "common.h"

#ifdef SHT11_DUMMY
#  warning SHT11 in dummy mode
#endif

//#if !defined SHT11_PIN_DATA || !defined SHT11_PIN_SCK
//#  error pin mapping missing
//#endif


// pin definitions
#define SHT11_PIN_DATA 3,3
#define SHT11_PIN_SCK  3,4



// sht11 address, unused anyway
#define SHT11_ADDRESS  (0x00 << 5)


// commands
#define SHT11_MEAS_TEMP  (SHT11_ADDRESS | 0x03)
#define SHT11_MEAS_RH    (SHT11_ADDRESS | 0x05)
#define SHT11_READ_STAT  (SHT11_ADDRESS | 0x07)
#define SHT11_WRITE_STAT (SHT11_ADDRESS | 0x06)
#define SHT11_SOFT_RESET (SHT11_ADDRESS | 0x1E)

enum {
  RES8,
  RES12
};

enum {
  SEND_ACK,
  SEND_NACK
};

enum {
  SHT11_STATUS_RESOLUTION,
  SHT11_STATUS_NO_RELOAD,
  SHT11_STATUS_HEATER,
  SHT11_STATUS_NA1,
  SHT11_STATUS_RES1,
  SHT11_STATUS_RES2,
  SHT11_STATUS_BAT,
  SHT11_STATUS_RES3
};


static inline void data_low(void) {
  clearpin3(SHT11_PIN_DATA);
  io_output3(SHT11_PIN_DATA);
}

static inline void data_release(void) {
  clearpin3(SHT11_PIN_DATA);
  io_input_dc_pullup3(SHT11_PIN_DATA);
}

static inline void sck_lo(void) {
  clearpin3(SHT11_PIN_SCK);
}

static inline void sck_hi(void) {
  setpin3(SHT11_PIN_SCK);
}


static inline void nopx(void) {
  nop(); nop();
}

static void write_bit(uint8_t bit) {

  /*
   * SCK  __/~~~\__
   *   	   	  
   *		  	
   * DATA X========X
   */


  if ( bit ) data_release();
  else data_low();
  _delay_ms(1);

  sck_hi(); _delay_ms(1);
  sck_lo(); _delay_ms(1);

  data_release();
}


static uint8_t read_bit(void) {
  uint8_t v = 0;

  sck_hi(); 
  if ( getpin3(SHT11_PIN_DATA) ) v = 1; 
  sck_lo();
  return v;
}


static void write_byte(uint8_t byte) {
  for (uint8_t i = 0x80;  i>0 ; i /= 2 ) {
	write_bit( byte & i );
  }

#ifndef SHT11_DUMMY
  uint8_t nack = read_bit();
  if (nack) uart_puts_P(" failed to receive ack" NEWLINE);
#endif

}


static uint8_t read_byte(uint8_t ack) {

  uint8_t v = 0;
  for (uint8_t i = 0x80; i>0; i/=2 ) {
	if (read_bit()) v |= i ;
	_delay_ms(1);
  }
  write_bit(ack);

  return v;
}

static void transmission_start(void) {

  /*
   * SCK  __/~~~\____/~~~\___
   *   	   	  |	   	   |
   *		  |		   |
   * DATA ~~~~\________/~~~~~
   */


  data_release();

  sck_hi();       _delay_ms(1);
  data_low();     _delay_ms(1);
  sck_lo();       _delay_ms(1);
  sck_hi();       _delay_ms(1);
  data_release(); _delay_ms(1);
  sck_lo();       _delay_ms(1);

}

static void connection_reset(void) {
  /*
   * SCK  __/~\_/~\_/~\_/~\_/~\_/~\_/~\_/~\_/~\_ (9x)
   * 
   * DATA ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ (always hi)
   */

  _delay_ms(1);

  data_release();

  for ( uint8_t i = 0; i < 9; i++) {
	sck_hi(); nopx();
	sck_lo(); nopx();
  }

  transmission_start();
}


static void status_register_write(uint8_t data) {
  transmission_start();
  write_byte(SHT11_WRITE_STAT);
  write_byte(data);
}


static uint8_t status_register_read(void) {
  uint8_t v, crc;
  transmission_start();
  write_byte(SHT11_READ_STAT);
  v = read_byte(SEND_ACK);
  crc = read_byte(SEND_NACK);
  return v;
}

static uint8_t read(uint8_t what) {

  uint8_t b1, b2, crc;

  transmission_start();
  write_byte(what);

#ifndef SHT11_DUMMY
  for ( uint8_t i = 0; i < 500; i++ ) {
	_delay_ms(1);
	if ( !getpin3(SHT11_PIN_DATA) ) break;
  }
  if (getpin3(SHT11_PIN_DATA) ) uart_puts_P("did not receive measurement" NEWLINE);
#endif

  b1 = read_byte(SEND_ACK);
  b2 = read_byte(SEND_ACK);
  
  crc = read_byte(SEND_NACK);

#if SHT11_RESOLUTION == 8

  if ( what == SHT11_MEAS_RH ) {
	
	// from the application note "RH and Temperature non-linearity compensation"

	uint16_t result;           
	uint8_t sensor_out;       
	sensor_out = (b1 << 8) | b2; 
	if ( sensor_out <= 107 ) {
	  result = 143 * sensor_out;
	  if (result < 512) result =  512;
	  result = result - 512;
	}
	else {
	  result = 111 * sensor_out;
	  result = result + 2893;
	  if (result > 25600) result  = 25600;
	}

	return result >> 8;
	  
  }

  if ( what == SHT11_MEAS_TEMP ) {
	uint16_t x = (b1 << 8) | b2;
	uint16_t y = x/25 -40;
	return (uint8_t) y;
  }

  return 0;
#elif SHT11_RESOLUTION == 12

# error "n.i."
#else
# error "invalid SHT11 resolution"
#endif


  uart_puts_P("illegal read call" NEWLINE);

}

static void soft_reset(void) {
  connection_reset();
  write_byte(SHT11_SOFT_RESET);
}

void sht11_init(void) {

  LOG_INIT();

  _delay_ms(10);

  io_input_no_pullup3(SHT11_PIN_DATA);
  io_output3(SHT11_PIN_SCK);

  sck_lo();
  data_release();

  connection_reset();

  // acc. datasheet p5
  _delay_ms(11);

  soft_reset();

#if SHT11_RESOLUTION==8
  status_register_write( (1<<SHT11_STATUS_RESOLUTION));
#endif
  LOG_INIT_EXIT();
}

uint8_t sht11_get_humidity(void) {

#if defined SHT11_DUMMY || defined SHT11_DUMMY_TMP101
  return 34;
#else
  return read(SHT11_MEAS_RH);
#endif
}

uint8_t sht11_get_temperature(void) {

#ifdef SHT11_DUMMY

  return 33;

#elif defined SHT11_DUMMY_TMP101

  return tmp101_gettemp(SHT11_DUMMY_TMP101);

#else
  return read(SHT11_MEAS_TEMP);
#endif
}
