/* 
 * terrarium control
 * mru, november 2009
 *
 * sensirion shtxx humidity/temperature sensor
 */


#define SHT11_RESOLUTION 8

extern void sht11_init(void);
extern uint8_t sht11_get_humidity(void);
extern uint8_t sht11_get_temperature(void);

