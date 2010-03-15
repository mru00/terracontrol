/* 
 * terrarium control
 * mru, november 2009
 *
 */


#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include "common.h"


static uint8_t is_busy(void);


enum {
  HD4478_REG_IR,
  HD4478_REG_DATA
};

enum {
  HD4478_CLEARDISPLAY
};

enum {
  HD4478_RETURNHOME = 1
};

enum {
  HD4478_ENTRYMODE_S,       // 
  HD4478_ENTRYMODE_ID,      //
  HD4478_ENTRYMODE
};

enum {
  HD4478_DISPLAY_B,         // B .. blinking
  HD4478_DISPLAY_C,         // C .. cursor
  HD4478_DISPLAY_D,         // D .. display on /off
  HD4478_DISPLAY
};


enum {
  HD4478_CURSOR_RL = 2,     // 
  HD4478_CURSOR_SC,         //
  HD4478_CURSOR
};


enum {
  HD4478_FUNCTIONSET_F = 2,  // F .. character font:= 0 => 5x8 font
  HD4478_FUNCTIONSET_N,      // N .. number of display lines: = 0 => 1-line
  HD4478_FUNCTIONSET_DL,     // DL .. datalength:  1 => 8-bit interface
  HD4478_FUNCTIONSET
};

enum {
  HD4478_SETCGRAM_ACG0,
  HD4478_SETCGRAM_ACG1,
  HD4478_SETCGRAM_ACG2,
  HD4478_SETCGRAM_ACG3,
  HD4478_SETCGRAM_ACG4,
  HD4478_SETCGRAM_ACG5,
  HD4478_SETCGRAM
};

enum {
  HD4478_SETDDRAM_ADD0,
  HD4478_SETDDRAM_ADD1,
  HD4478_SETDDRAM_ADD2,
  HD4478_SETDDRAM_ADD3,
  HD4478_SETDDRAM_ADD4,
  HD4478_SETDDRAM_ADD5,
  HD4478_SETDDRAM_ADD6,
  HD4478_SETDDRAM
};


enum {
  HD4478_BUSY_FLAG = 7          // busy flag
};


// utility functions



static void write_nibble ( uint8_t rs, uint8_t data) {


  // configure as output
  HD4478_DB_C |= 0x0f;
  HD4478_DB_W &= 0xf0;

  clearpin2(HD4478_RW);
  xpin2(rs, HD4478_RS);
  nop();  nop();

  setpin2(HD4478_E);

  nop();  nop();
  // clear low-nibble of HD4478_DB
  HD4478_DB_W |= data & 0x0f;
  nop();  nop();
  clearpin2(HD4478_E);
  nop(); nop();

  setpin2(HD4478_E);

  nop();  nop();
}


static void write ( uint8_t rs, uint8_t data) {
  write_nibble(rs, data >> 4);
  nop(); nop();

  write_nibble(rs, data);
  nop(); nop();
  while (is_busy());
}


static uint8_t read_nibble ( uint8_t rs ) {

  uint8_t data = 0;


  // disable pull-ups
  HD4478_DB_W |= 0x0f;
  // configure as input
  HD4478_DB_C &= 0xf0;

  setpin2(HD4478_RW);
  xpin2(rs, HD4478_RS);
  nop(); nop();
  setpin2(HD4478_E);
  nop();  nop();
  data = HD4478_DB_R & 0x0f;
  nop();  nop();
  clearpin2(HD4478_E);

  nop(); nop();

  return data;
}

static uint8_t read ( uint8_t rs ) {
  return read_nibble(rs) << 4 | read_nibble(rs);
}

static uint8_t is_busy(void) {

#ifdef HD4478_DUMMY
  return 0;
#else
  return (read(HD4478_REG_IR) & _BV(HD4478_BUSY_FLAG)) != 0;
#endif
}


// public interface:

void hd4478_init(void) {

  LOG_INIT();

  // function set (8 bit interface), #1
  write_nibble(HD4478_REG_IR, 
			   ((1<<HD4478_FUNCTIONSET) | 
				(1<<HD4478_FUNCTIONSET_N) | 
				(0<<HD4478_FUNCTIONSET_F) |
				(1<<HD4478_FUNCTIONSET_DL)) >> 4);
			   
  _delay_ms(5);
  
  // function set (8 bit interface), #2
  write_nibble(HD4478_REG_IR, 
			   ((1<<HD4478_FUNCTIONSET) | 
				(1<<HD4478_FUNCTIONSET_N) | 
				(0<<HD4478_FUNCTIONSET_F) |
				(1<<HD4478_FUNCTIONSET_DL)) >> 4);
			   
  _delay_ms(1);
			   
  // function set (8 bit interface), #3
  write_nibble(HD4478_REG_IR, 
			   ((1<<HD4478_FUNCTIONSET) | 
				(1<<HD4478_FUNCTIONSET_N) | 
				(0<<HD4478_FUNCTIONSET_F) |
				(1<<HD4478_FUNCTIONSET_DL)) >> 4 );

			   
  _delay_ms(1);

  // function set (4 bit interface)
  write_nibble(HD4478_REG_IR, 
			   ((1<<HD4478_FUNCTIONSET) | 
				(1<<HD4478_FUNCTIONSET_N) | 
				(0<<HD4478_FUNCTIONSET_F) |
				(0<<HD4478_FUNCTIONSET_DL)) >> 4);


  // function set ( N=1, F = 0, DL = 0)
  write(HD4478_REG_IR, 
		(1<<HD4478_FUNCTIONSET) | 
		(1<<HD4478_FUNCTIONSET_N) | 
		(0<<HD4478_FUNCTIONSET_F) |
		(0<<HD4478_FUNCTIONSET_DL));
  
  

  write(HD4478_REG_IR, 
		(1<<HD4478_DISPLAY) | 
		(1<<HD4478_DISPLAY_D) | 
		(0<<HD4478_DISPLAY_C) |
		(0<<HD4478_DISPLAY_B) );

  // clear display
  write(HD4478_REG_IR, 
		(1<<HD4478_CLEARDISPLAY) );

  write(HD4478_REG_IR, 
		(1<<HD4478_ENTRYMODE) | 
		(1<<HD4478_ENTRYMODE_ID) | 
		(0<<HD4478_ENTRYMODE_S) );

  write(HD4478_REG_IR, 
		(1<<HD4478_RETURNHOME) );

  LOG_INIT_EXIT();
}

void hd4478_moveto(const uint8_t r, const uint8_t c) {
  uint8_t adr = 0x40 * r + c;
  // write the address to the DDRAM
  write(HD4478_REG_IR,
		(1<<HD4478_SETDDRAM) |
		(adr & 0x7F));
}


void hd4478_putc(const char character) {
  // write a character to current position
  write(HD4478_REG_DATA,
		//_BV(HD4478_SETCGRAM)) |
		(character & 0x7f));

  // something went wrong here. i tried to adhere to the documentation
  // of the hd4478, but the _BV... hinders the display of
  // number. anyways, this way it seems to work.
}

void hd4478_puts(const char* string) {
  while (*string != '\0') 
	hd4478_putc(*string ++);
}

void hd4478_clear(void) {
  // clear display
  write(HD4478_REG_IR, 
		(1<<HD4478_CLEARDISPLAY) );

  hd4478_moveto(0, 0);
}
