/* 
 * terrarium control
 * mru, november 2009
 *
 */

#include <avr/eeprom.h>
#include <stdio.h>

#include "common.h"

#define VALID_MASK 0xA5

uint8_t ee_valid_configuration EEMEM;

time_t ee_daytime[2] EEMEM;
uint8_t ee_tempsetpoint[2] EEMEM;
uint8_t ee_humiditysetpoint[2] EEMEM;

struct timeswitch_t ee_timeswitches[N_TIMESWITCHES] EEMEM;

void eeprom_init(void) {

  LOG_INIT();
  
  uint8_t i;

  if ( eeprom_read_byte(&ee_valid_configuration) != VALID_MASK) {

	time_t t[2];
	t[0] = time_from_hms(8, 0, 0);
	t[1] = time_from_hms(20, 0, 0);

	for ( int i = 0; i< 2; i ++ ) {
	  daytime[i] = t[i];

	  temp_setpoint[i] = 20;
	  eeprom_write_byte(& ee_tempsetpoint[i], temp_setpoint[i]);
	
	  humidity_setpoint[i] = 30;
	  eeprom_write_byte(& ee_humiditysetpoint[i], humidity_setpoint[i]);

	  eeprom_write_block( (const void*) &daytime[i], &ee_daytime[i], sizeof(time_t));
	}

	
	timeswitch_set(0, 
				   time_from_hms(11, 0, 0), 
				   time_from_hms(13, 0, 0), 
				   OUTPUT_L1, 
				   1);

	timeswitch_set(1, 
				   time_from_hms(10, 0, 0), 
				   time_from_hms(14, 0, 0), 
				   OUTPUT_L2, 
				   1);

	timeswitch_set(2, 
				   time_from_hms(10, 0, 0), 
				   time_from_hms(14, 0, 0), 
				   OUTPUT_HEATING_LAMP, 
				   1);

	for ( i = 3; i < N_TIMESWITCHES; i++ )
	  timeswitch_set(i, 0, 0, 0, 0);


	eeprom_write_byte(&ee_valid_configuration, VALID_MASK);

	return;
  }
  
  for (int i = 0; i < 2; i++ ) {
	temp_setpoint[i] = eeprom_read_byte(&ee_tempsetpoint[i]);
	humidity_setpoint[i] = eeprom_read_byte(&ee_humiditysetpoint[i]);
	eeprom_read_block( (void*) &daytime[i], &ee_daytime[i], sizeof(time_t));
  }

  for ( i = 0; i < N_TIMESWITCHES; i++ ) {
	eeprom_read_block( (void*) &timeswitches[i], &ee_timeswitches[i], sizeof(struct timeswitch_t) );
  }

  LOG_INIT_EXIT();
}
