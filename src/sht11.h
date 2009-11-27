/* 
 * terrarium control
 * mru, november 2009
 *
 * sensirion sht1x humidity/temperature sensor
 */




#define SHT11_RESOLUTION 8
#define SHT11_DUMMY
#define SHT11_DEBUG


extern void sht11_init(void);
extern uint8_t sht11_get_humidity(void);
extern uint8_t sht11_get_temperature(void);

