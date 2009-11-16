/* 
 * terrarium control
 * mru, november 2009
 *
 */


#pragma once


#define SECONDS_PER_DAY 86400


#define H(t) ((t/3600))
#define M(t) ((t / 60 - H(t)*60))
#define S(t) (t  - (H(t)*3600 + M(t)*60))

#define TIME_PRINTF_MASK "%02d:%02d:%02d"
#define TIME_PRINTF_DATA(t) (uint8_t)H(t), (uint8_t)M(t), (uint8_t)S(t)


extern time_t volatile current_time;


extern void time_init(void);

extern void time_current_print(void);
extern void time_print(time_t);


/* 
 * returns true if the time was updated since last call of this function 
 */
extern bool time_updated(void);

extern time_t const time_now(void);
