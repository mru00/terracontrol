/* 
 * terrarium control
 * mru, november 2009
 *
 */

#pragma once


// enable this define to run the dummy version, i.e. with no display connected

#define HD4478_DUMMY


// public interface:

extern void hd4478_init(void);

extern void hd4478_moveto(uint8_t r, uint8_t c);

extern void hd4478_putc(char character);

extern void hd4478_puts(char* string);

extern void hd4478_clear(void);

