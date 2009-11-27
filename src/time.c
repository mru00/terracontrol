/* 
 * terrarium control
 * mru, november 2009
 *
 */


#include <avr/interrupt.h>

#include "common.h"

date_t current_date;
time_t current_time;
static uint8_t volatile newtime;


ISR(INT0_vect) {
  newtime++;
}

void time_init(void) {

  LOG_INIT();

  DDRD &= ~(1 << PD2);

  MCUCR |= ( (1<<ISC01) | (1<<ISC00));  //The rising edge of INT0 generates an interrupt request.  
  GICR |= (1<< INT0);  //enable external interrupt 0

  newtime = 0;

  LOG_INIT_EXIT();
}


bool time_updated(void) {
  if ( newtime  ) {

	current_time = ds1307_gettime();
	current_date = ds1307_getdate();

	newtime --;
	return 1;
  }
  return 0;
}



