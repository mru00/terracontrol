/* 
 * terrarium control
 * mru, november 2009
 *
 * functions to control the timeswitches
 *
 */


#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stdio.h>

#include "common.h"

struct timeswitch_t timeswitches[N_TIMESWITCHES];



void timeswitch_init(void) {
  LOG_INIT();
}




void timeswitch_check(time_t now) {
  
  uint8_t i, j;
  uint8_t x;
  uint8_t values = {0,};
  uint8_t care = {0,};


  for ( i = 0; i < N_TIMESWITCHES; i ++ ) {

	if ( ! (timeswitches[i].output & OUTPUT_ENABLED_MASK) ) 
	  continue;

	// if the on-time goes over midnight, special case

	// create a map of all output that are handled by the timeswitches.
	// or together the outputs

	// this allows to have multiple timers on one output.


	if ( timeswitches[i].on < timeswitches[i].off )
	  x = now >= timeswitches[i].on && now <= timeswitches[i].off;
	else
	  x = now >= timeswitches[i].on  || now <= timeswitches[i].off;

	care |= 1 << (timeswitches[i].output & ~OUTPUT_ENABLED_MASK);
	values |= x << (timeswitches[i].output & ~OUTPUT_ENABLED_MASK);
  }

  // set all pins that were handled by the timers
  for ( j = 0; j < 8; j++ ) {
	if ( (care & (1<<j)) ) {
#ifdef TIMESWITCH_DEBUG
	  printf(" timeswitch: setting %d to %d\r\n", j, (values & _BV(j))?1:0);
#endif
	  portmap_setpin(values & (1<<j), j);
	}
  }

}


void timeswitch_set(uint8_t id, time_t on, time_t off, uint8_t output, uint8_t enabled) {

  if ( id < 0 || id >= N_TIMESWITCHES ) {
	puts("illegal timeswitch id");
  }
  
  timeswitches[id].on = on;
  timeswitches[id].off = off;
  timeswitches[id].output = output | (enabled ? OUTPUT_ENABLED_MASK : 0);

  eeprom_write_block(&timeswitches[id], &ee_timeswitches[id], sizeof(struct timeswitch_t));
}
