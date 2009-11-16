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
  struct port_pin_t pin;

  uint8_t enabled : 1;

};



#define N_TIMESWITCHES 4


extern void timeswitch_init(void);
extern void timeswitch_check(time_t now);
extern void timeswitch_set(uint8_t id, time_t on, time_t off, uint8_t port, uint8_t pin);



