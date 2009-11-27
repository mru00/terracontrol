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

inline uint8_t const __attribute__((pure))
time_in_range(const time_t begin, const time_t end) {
  time_t now = time_now();
  if ( begin < end )
	return now >= begin && now <= end;

  return now >= begin  || now <= end;
}

inline uint8_t const __attribute__((pure))
time_is_daytime(void) {
  return time_in_range(daytime[DAYTIME_BEGIN], daytime[DAYTIME_END]);
}

inline uint8_t time_get_s(const time_t t) { return t & 0xff; }
inline uint8_t time_get_m(const time_t t) { return (t>>8) & 0xff; }
inline uint8_t time_get_h(const time_t t) { return (t>>16) & 0xff; }

inline void time_print(time_t time) {
  char buf[4];
  uart_puts(itoat(time_get_h(time), buf));
  uart_putc(':');
  uart_puts(itoat(time_get_m(time), buf));
  uart_putc(':');
  uart_puts(itoat(time_get_s(time), buf));
}

inline void time_daytime_print(void) {
  time_print(daytime[DAYTIME_BEGIN]);
  uart_putc(' ');
  time_print(daytime[DAYTIME_END]);
}

// h, m, s must be in decimal!
inline time_t time_from_hms(const uint32_t h, const uint32_t m, const uint32_t s) {
  return (h << 16) + (m << 8) + (s);
}




inline uint8_t date_get_y(const date_t t) { return t & 0xff; }
inline uint8_t date_get_m(const date_t t) { return (t>>8) & 0xff; }
inline uint8_t date_get_d(const date_t t) { return (t>>16) & 0xff; }


inline void date_print(date_t date) {
  char buf[4];
  uart_puts(itoat(date_get_d(date), buf));
  uart_putc('.');
  uart_puts(itoat(date_get_m(date), buf));
  uart_putc('.');
  uart_puts(itoat(date_get_y(date), buf));
}

inline date_t date_now(void) {
  return current_date;
}

// d, m, y must be in decimal!
inline date_t date_from_dmy(const uint32_t d, const uint32_t m, const uint32_t y) {
  return (d << 16) + (m << 8) + (y);
}
