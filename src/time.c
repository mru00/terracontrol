/* 
 * terrarium control
 * mru, november 2009
 *
 */


#include <avr/interrupt.h>
#include <stdio.h>

#include "common.h"

time_t volatile current_time;

static uint8_t volatile newtime;


ISR(INT0_vect) {
  newtime++;
  current_time = ds1307_gettime();
}

void time_init(void) {

  LOG_INIT();

  DDRD &= ~(1 << PD2);

  MCUCR |= ( (1<<ISC01) | (1<<ISC00));  //The rising edge of INT0 generates an interrupt request.  
  GICR |= (1<< INT0);  //enable external interrupt 0

  newtime = 0;
}


bool time_updated(void) {
  if ( newtime  ) {
	newtime --;
	return 1;
  }
  return 0;
}

