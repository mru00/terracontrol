/*
 * terrarium control
 * mru, november 2009
 *
 */
#include <avr/io.h>
#include <util/delay.h>


#include "common.h"


#if SHT11_RESOLUTION == 8
# define HUM_LIN(so) ( so < 107 ? ((-230 + 138 * so) / 256) : ((1306 + 122*so)/256) )
#elif SHT11_RESOLUTION == 12
# error "n.i."
#else
# error "invalid SHT11 resolution"
#endif


#define SHT11_DATA_PORT PORTD
#define SHT11_DATA_PIN PD3

#define SHT11_SCK_PORT  PORTD
#define SHT11_SCK_PIN  PD4


#define SHT11_SCK  &SHT11_DATA_PORT,SHT11_SCK_PIN
#define SHT11_DATA &SHT11_DATA_PORT,SHT11_DATA_PIN

#define SHT11_MEAS_TEMP  0x03
#define SHT11_MEAS_RH    0x05
#define SHT11_READ_STAT  0x07
#define SHT11_WRITE_STAT 0x06
#define SHT11_SOFT_RESET   0x1E

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

  xpin2(bit, SHT11_DATA); nopx(); 
  setpin2(SHT11_SCK);     nopx(); 
  clearpin2(SHT11_SCK);   nopx(); 
}


static uint8_t read_bit(void) {
  uint8_t v = 0;
  setpin2(SHT11_SCK);
  if ( PIND & PD3 ) v = 1;
  clearpin2(SHT11_SCK);
  return v;
}


static void write_byte(uint8_t byte) {
  for (uint8_t i = 0x80;  i ; i >>= 2 ) {
	write_bit( byte & i );
  }

#ifdef SHT11_DUMMY
  read_bit();

#else

  uint8_t nack = read_bit();

  if (nack) {
	uart_puts(" failed to receive ack");
  }
#endif

}


static uint8_t read_byte(uint8_t ack) {

  uint8_t v = 0;
  for (uint8_t i = 0; i < 8; i++ ) {
	v = v << 1;
	v |= read_bit();
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


  // data should be "1" here anyway
  setpin2(SHT11_DATA);
  clearpin2(SHT11_SCK);    nopx();

  clearpin2(SHT11_DATA); nopx();
  clearpin2(SHT11_SCK);  nopx();
  setpin2(SHT11_SCK);    nopx();
  setpin2(SHT11_DATA);   nopx();
  clearpin2(SHT11_SCK);  nopx();
}

static void connection_reset(void) {
  /*
   * SCK  __/~\_/~\_/~\_/~\_/~\_/~\_/~\_/~\_/~\_ (9x)
   * 
   * DATA ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ (always hi)
   */

  setpin2(SHT11_DATA);  nop(); nop();

  for ( uint8_t i = 0; i < 9; i++) {
	setpin2(SHT11_SCK); nop();nop();
	clearpin2(SHT11_SCK); nop();nop();
  }

  transmission_start();
}


static void status_register_write(uint8_t data) {
  transmission_start();
  write_byte(SHT11_WRITE_STAT);
  write_byte(data);
}

/*
static uint8_t status_register_read(void) {

  uint8_t v, crc;
  transmission_start();
  write_byte(SHT11_READ_STAT);
  v = read_byte(SEND_ACK);
  crc = read_byte(SEND_NACK);
  return v;
}
*/

static uint8_t read(uint8_t what) {

  uint8_t b1, b2, crc;

  transmission_start();
  write_byte(what);

#ifndef SHT11_DUMMY
  loop_until_bit_is_clear(PIND, PD3);
#endif

  b1 = read_byte(SEND_ACK);
  b2 = read_byte(SEND_ACK);
  
  crc = read_byte(SEND_NACK);

  return b2;
}


/*
static void soft_reset(void) {
  connection_reset();
  write_byte(SHT11_SOFT_RESET);
}
*/

void sht11_init(void) {

  LOG_INIT();

  //  _delay_ms(10);

  DDRD |= _BV(PD3) | _BV(PD4);

  SHT11_DATA_PORT |= _BV(SHT11_DATA_PIN);
  SHT11_SCK_PORT | _BV(SHT11_SCK_PIN);

  connection_reset();

  // acc. datasheet p5
  //  _delay_ms(11);


#if SHT11_RESOLUTION==8
  status_register_write( (1<<SHT11_STATUS_RESOLUTION));
#endif
  LOG_INIT_EXIT();
}



uint8_t sht11_get_humidity(void) {
#ifdef SHT11_DUMMY
  return 34;
#else
  return (uint8_t) HUM_LIN( (uint32_t)read(SHT11_MEAS_RH));
#endif
}
#define TMP101_ID 1

uint8_t sht11_get_temperature(void) {

#ifdef SHT11_DUMMY
  return tmp101_gettemp(TMP101_ID);
#else
  //  return read(SHT11_MEAS_TEMP);

#  warning sht11_get_temperature not implemented

#endif
}
