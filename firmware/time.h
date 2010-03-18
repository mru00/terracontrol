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

extern time_t current_time;
extern date_t current_date;

typedef void (*t_puts)(const char*);

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

inline date_t const __attribute__((pure)) 
date_now(void) {
  return current_date;
}

extern uint8_t time_in_range(const time_t begin, const time_t end);

inline uint8_t const __attribute__((pure))
time_is_daytime(void) {
  return time_in_range(settings.daytime[DAYTIME_BEGIN], settings.daytime[DAYTIME_END]);
}

#ifdef TIME_STRUCT
inline uint8_t const __attribute__((pure)) time_get_s(const time_t t) { return t.s; }
inline uint8_t const __attribute__((pure)) time_get_m(const time_t t) { return t.m; }
inline uint8_t const __attribute__((pure)) time_get_h(const time_t t) { return t.h; }
#else
inline uint8_t const __attribute__((pure)) time_get_s(const time_t t) { return t & 0xff; }
inline uint8_t const __attribute__((pure)) time_get_m(const time_t t) { return (t>>8) & 0xff; }
inline uint8_t const __attribute__((pure)) time_get_h(const time_t t) { return (t>>16) & 0xff; }
#endif



extern char* ttoa(const time_t time, char* buf);
extern void date_print(const date_t date);


// h, m, s must be in decimal!
inline time_t const __attribute__((pure)) 
time_from_hms(const uint8_t h, const uint8_t m, const uint8_t s) {

#ifdef TIME_STRUCT
  time_t t;
  t.h = h;
  t.m = m;
  t.s = s;
  return t;
#else
  return ((uint32_t)h << 16) + ((uint32_t)m << 8) + ((uint32_t)s);
#endif
}

inline uint8_t const __attribute__((pure)) 
date_get_y(const date_t t) { return t & 0xff; }

inline uint8_t const __attribute__((pure)) 
date_get_m(const date_t t) { return (t>>8) & 0xff; }

inline uint8_t const __attribute__((pure)) 
date_get_d(const date_t t) { return (t>>16) & 0xff; }

// d, m, y must be in decimal!
inline date_t const __attribute__((pure)) 
date_from_dmy(const uint32_t d, const uint32_t m, const uint32_t y) {
  return (d << 16) + (m << 8) + (y);
}
