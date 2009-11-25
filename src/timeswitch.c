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

struct timeswitch_t volatile timeswitches[N_TIMESWITCHES];

void timeswitch_init(void) {
  LOG_INIT();
}

void timeswitch_check(time_t now) {
  
  uint8_t i, j;

  uint8_t values = {0,};
  uint8_t care = {0,};

  for ( i = 0; i < N_TIMESWITCHES; i ++ ) {

	if ( ! timeswitch_enabled(i) ) continue;

	// create a map of all output that are handled by the timeswitches.
	// or together the outputs

	// this allows to have multiple timers on one output.

	care   |= 1 << (timeswitches[i].output & ~OUTPUT_ENABLED_MASK);
	values |= timeswitch_active(i) << (timeswitches[i].output & ~OUTPUT_ENABLED_MASK);
  }

  // set all pins that were handled by the timers
  for ( j = 0; j < 8; j++ ) {
	if ( (care & _BV(j)) ) portmap_setpin(values & (1<<j), j);
  }
}


void timeswitch_set(uint8_t id, time_t on, time_t off, uint8_t output, uint8_t enabled) {

#ifdef TIMESWITCH_DEBUG
  if ( id < 0 || id >= N_TIMESWITCHES ) {
	uart_puts("illegal timeswitch id" NEWLINE);
  }
#endif

  timeswitches[id].on = on;
  timeswitches[id].off = off;
  timeswitches[id].output = output | (enabled ? OUTPUT_ENABLED_MASK : 0);

  eeprom_write_block( ( const void*) &timeswitches[id], &ee_timeswitches[id], sizeof(struct timeswitch_t));
}
