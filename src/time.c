/* 
 * terrarium control
 * mru, november 2009
 *
 */


#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <avr/wdt.h>
#include <util/delay.h>

#include <stdio.h>

#include "common.h"


time_t volatile current_time;

static uint8_t volatile newtime;


ISR(INT0_vect) {
  newtime = 1;
  current_time = ds1307_gettime();
}


void time_init(void) {

  DDRD &= ~(1 << PD2);

  MCUCR |= ( (1<<ISC01) | (1<<ISC00));  //The rising edge of INT0 generates an interrupt request.  
  GICR |= (1<< INT0);  //enable external interrupt 0

  newtime = 0;
}

void time_current_print(void) {
  time_print(current_time);
}

void time_print(time_t t) {
  uint8_t h = t / 3600;
  uint8_t m = t / 60 - h*60;
  uint8_t s = t  - (h*3600 + m*60);
  printf("%02d:%02d:%02d", h, m, s);
}

bool time_updated(void) {
  if ( newtime ) {
	newtime = 0;
	return 1;
  }
  return 0;
}

time_t const time_now(void) {
  return current_time;
}

