/* 
 * terrarium control
 * mru, november 2009
 *
 */

#pragma once


// enable this define to run the dummy version, i.e. with no display connected

//#define HD4478_DUMMY

#define HD4478_RS &PORTD, PD5
#define HD4478_RW &PORTD, PD6
#define HD4478_E  &PORTD, PD7
#define HD4478_DB_W PORTC
#define HD4478_DB_R PINC
#define HD4478_DB_C DDRC



// public interface:

extern void hd4478_init(void);

extern void hd4478_moveto(const uint8_t r, const uint8_t c);

extern void hd4478_putc(const char character);

extern void hd4478_puts(const char* string);

extern void hd4478_clear(void);

