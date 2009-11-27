/* 
 * terrarium control
 * mru, november 2009
 *
 */


extern char* itoa8(uint8_t value, char* buf);

// itoa for one time part. always two digits, eventually 
// with leading zero
extern char* itoat(uint8_t value, char* buf);

extern uint8_t __attribute__((pure)) atoi8(char* buf);


extern uint8_t __attribute__((pure)) is_digit (char d);
extern uint8_t __attribute__((pure)) is_number(char* s);
