/* 
 * terrarium control
 * mru, november 2009
 *
 * functions to control the timeswitches
 *
 */


#pragma once

struct timeswitch_t {
  time_t on, off;
  uint8_t output;   // sign bit is enabled flag!
};

#define N_TIMESWITCHES 4
#define TIMESWITCH_STR_SIZE 2*TIME_STR_SIZE + 4 + 2 + 1

#define OUTPUT_ENABLED_MASK 0x80

//#define TIMESWITCH_DEBUG


extern struct timeswitch_t volatile timeswitches[N_TIMESWITCHES];


// module initializer
extern void timeswitch_init(void);

// check all timeswitches, act accordingly
extern void timeswitch_check(time_t now);

// configure a timer
extern void timeswitch_set(uint8_t id, time_t on, time_t off, uint8_t output, uint8_t enabled);


// ==== timer status functions:


// return 1 if the timeswitch is currently considered to switching
//        0 otherwise
inline uint8_t __attribute__((pure)) 
timeswitch_enabled(const uint8_t id)   {
  return timeswitches[id].output & OUTPUT_ENABLED_MASK ? 1 : 0;
}


// return 1 if the timeswitch is currently switched on
//        0 otherwise
inline uint8_t __attribute__((pure)) 
timeswitch_active(const uint8_t id)   {
  if ( !timeswitch_enabled(id) ) return 0;
  return time_in_range(timeswitches[id].on, timeswitches[id].off);
}


inline void  timeswitch_print(uint8_t id) {
  
  char buf[4];

  time_print(timeswitches[id].on);
  uart_putc(' ');
  time_print(timeswitches[id].off);
  uart_putc(' ');
  uart_puts(itoa8(timeswitches[id].output & ~OUTPUT_ENABLED_MASK, buf));
  uart_putc(' ');
  uart_puts(itoa8(timeswitch_enabled(id), buf));
  uart_putc(' ');
  uart_puts(itoa8(timeswitch_active(id), buf));
}

