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


#define H(t) ((t/3600UL))
#define M(t) ((t / 60UL) - H(t)*60UL)
#define S(t) (t  - (H(t)*3600UL + M(t)*60UL))

// abstract printf 
#define TIME_PRINTF_MASK "%02u:%02u:%02u (=%lu)"
#define TIME_PRINTF_DATA(t) (uint8_t)H(t), (uint8_t)M(t), (uint8_t)S(t), current_time

// an example:
#define print_current_time() do { printf( TIME_PRINTF_MASK, TIME_PRINTF_DATA(time_now())); } while (0)



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
