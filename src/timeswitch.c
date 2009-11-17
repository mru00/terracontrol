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

static struct timeswitch_t timeswitches[N_TIMESWITCHES];



void timeswitch_init(void) {
  LOG_INIT();
}




void timeswitch_check(time_t now) {
  
  uint8_t i, j;
  uint8_t x;
  uint8_t values[4] = {0,};
  uint8_t care[4] = {0,};


  for ( i = 0; i < N_TIMESWITCHES; i ++ ) {

	if ( !timeswitches[i].enabled ) 
	  continue;

	// if the on-time goes over midnight, special case

	// create a map of all output that are handled by the timeswitches.
	// or together the outputs

	// this allows to have multiple timers on one output.


	if ( timeswitches[i].on < timeswitches[i].off )
	  x = now >= timeswitches[i].on && now <= timeswitches[i].off;
	else
	  x = now >= timeswitches[i].on  || now <= timeswitches[i].off;

	care[timeswitches[i].portpin.po] |= (1 << timeswitches[i].portpin.pi);
	values[timeswitches[i].portpin.po] |= (x << timeswitches[i].portpin.pi);
  }


  // set all pins that were handled by the timers
  for (i = 0; i < 4; i ++ ) 
	for ( j = 0; j < 8; j++ ) 
	  if ( (care[i] & (1<<j)) ) 
		xpin2( values[i] & (1<<j), i, j );

}


void timeswitch_set(uint8_t id, time_t on, time_t off, struct port_pin_t port) {

  if ( id < 0 || id >= N_TIMESWITCHES ) {
	puts("illegal timeswitch id");
  }
  
  timeswitches[id].on = on;
  timeswitches[id].off = off;
  timeswitches[id].portpin = port;
  timeswitches[id].enabled = 1;

  clearpin(port);
  setup_as_output(port);  
}
