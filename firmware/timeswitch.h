/* 
 * terrarium control
 * mru, november 2009
 *
 * functions to control the timeswitches
 *
 */


#pragma once


#define OUTPUT_ENABLED_MASK 0x80

extern void timeswitch_init(void);

// check all timeswitches
// output_values is interpreted as a bitmask,
// for every output it will contain a 
//   1 if the output is enabled
//   0 otherwise
extern void timeswitch_check(void);

// configure a timer
extern void timeswitch_set(const uint8_t id, 
						   const time_t on, 
						   const time_t off, 
						   const uint8_t output, 
						   const uint8_t enabled);

extern void timeswitch_commit(void);


// ==== timer status functions:


// return 1 if the timeswitch is currently considered to switching
//        0 otherwise
inline uint8_t __attribute__((pure)) 
timeswitch_enabled(const uint8_t id)   {
  return settings.timeswitches[id].output & OUTPUT_ENABLED_MASK ? 1 : 0;
}


// return 1 if the timeswitch is currently switched on
//        0 otherwise
inline uint8_t __attribute__((pure)) 
timeswitch_active(const uint8_t id)   {
  if ( !timeswitch_enabled(id) ) return 0;
  return time_in_range(settings.timeswitches[id].on, settings.timeswitches[id].off);
}
