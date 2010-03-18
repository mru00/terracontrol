/* 
 * terrarium control
 * mru, november 2009
 *
 *
 * watchdog functions
 *
 */



inline void watchdog_enable(uint8_t prescaler) {
  cli();
  _WDR();
  WDTCR |= _BV(WDCE) | _BV(WDE) | (prescaler & 0x7);
  sei();
}


inline void watchdog_disable(void) {
  cli();
  _WDR();
  WDTCR |= _BV(WDCE) | _BV(WDE);
  WDTCR = 0x00;
  sei();
}


inline void watchdog_reset(void) {
  _WDR();
}
