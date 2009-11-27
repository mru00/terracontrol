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

#define N_TIMESWITCHES 8

#define OUTPUT_ENABLED_MASK 0x80

//#define TIMESWITCH_DEBUG


extern struct timeswitch_t volatile timeswitches[N_TIMESWITCHES];


// module initializer
extern void timeswitch_init(void);

// check all timeswitches
// output_values is interpreted as a bitmask,
// for every output it will contain a 
//   1 if the output is enabled
//   0 otherwise
extern void timeswitch_check(const time_t now,
							 uint8_t* output_values);

// configure a timer
extern void timeswitch_set(const uint8_t id, 
						   const time_t on, 
						   const time_t off, 
						   const uint8_t output, 
						   const uint8_t enabled);


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

