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


extern struct timeswitch_t timeswitches[N_TIMESWITCHES];


extern void timeswitch_init(void);
extern void timeswitch_check(time_t now);
extern void timeswitch_set(uint8_t id, time_t on, time_t off, uint8_t output, uint8_t enabled);

inline char* timeswitch_str(char* buffer, uint8_t id) {

  char t_buf1[TIME_STR_SIZE];
  char t_buf2[TIME_STR_SIZE];

  sprintf(buffer, 
		  "%s %s %d %d", 
		  time_str(t_buf1, timeswitches[id].on), 
		  time_str(t_buf2, timeswitches[id].off), 
		  timeswitches[id].output & ~OUTPUT_ENABLED_MASK,
		  timeswitches[id].output & OUTPUT_ENABLED_MASK ? 1 : 0);

  return buffer;
}

