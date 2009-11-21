/* 
 * terrarium control
 * mru, november 2009
 *
 *
 * uses:
 *  - external interrupt INT0
 *  - pin PORTD/PD2
 *  
 *  - module i2c 
 *  - module ds1307 
 */


#pragma once


#define SECONDS_PER_DAY 86400
#define TIME_STR_SIZE 9

extern time_t volatile current_time;


/*
 * init the time module;
 * sets up interrupt, ...
 */
extern void time_init(void);


/* 
 * returns true if the time was updated since last call of this function
 */
extern bool time_updated(void);


inline time_t const __attribute__((pure)) 
time_now(void) {
  return current_time;
}



inline uint8_t time_get_s(time_t t) { return t & 0xff; }
inline uint8_t time_get_m(time_t t) { return (t>>8) & 0xff; }
inline uint8_t time_get_h(time_t t) { return (t>>16) & 0xff; }


// tostring. 
// returns buf again, to be used in something like: 
//  puts(time_str(buffer, time_now()));
inline char* time_str(char* buf, time_t time) {
  sprintf(buf, "%02d:%02d:%02d" , time_get_h(time), time_get_m(time), time_get_s(time) );
  return buf;
}

// h, m, s must be in decimal!
inline time_t time_from_hms(uint32_t h, uint32_t m, uint32_t s) {
  return (h << 16) + (m << 8) + (s);
}



