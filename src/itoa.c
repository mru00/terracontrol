/* 
 * terrarium control
 * mru, november 2009
 *
 */


#include <avr/io.h>

#include "common.h"


char* itoa8(uint8_t value, char* buf) {

  uint8_t h, t, o;  // hundreds, tens, ones
  h = value / 100;
  t = (value - 100*h) / 10;
  o = (value - 100*h - 10*t);

  if ( h != 0 ) {
	buf[0] = '0' + h; 
	buf[1] = '0' + t;
	buf[2] = '0' + o;
	buf[3] = '\0';
  }
  else if ( t != 0 ) {
	buf[0] = '0' + t;
	buf[1] = '0' + o;
	buf[2] = '\0';
  }
  else {
	buf[0] = '0' + o;
	buf[1] = '\0';
  }

  return buf;
}

// itoa for one time part. always two digits, eventually 
// with leading zero
char* itoat(uint8_t value, char* buf) {

  uint8_t t, o;
  t = value / 10;
  o = (value - 10*t);

  buf[0] = '0' + t;
  buf[1] = '0' + o;
  buf[2] = '\0';

  return buf;
}

uint8_t __attribute__((pure))
atoi8(char* buf) {

  uint8_t value;

  value = 0;
  while( is_digit(*buf) ) {
	value *= 10;
	value += *buf - '0';
	buf++;
  }

  return value;
}



uint8_t __attribute__((pure))
is_digit (char d) {
  return d >= '0' && d <= '9';
}

uint8_t __attribute__((pure))
is_number(char* s) {
  do {
	if ( !is_digit(*s) )  return 0;
	s++;
  } while ( *s != '\0');
  return 1;
}
