/* 
 * terrarium control
 * mru, november 2009
 *
 * serial commandline interface
 */

#include <avr/io.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "common.h"


#define MAX_LINE 30

static char current_line[MAX_LINE];
static char* current_pos;
static char* tokenize_pos;
static char* additional_text = NULL;
static char separator[] = " ";

static char str_fail[] = "FAIL";
static char str_ok[] = "OK";
static char str_empty[] = "";

static uint8_t parse_fail = 0;

#define checked(stmt)  stmt; if(parse_fail) return


static void parse(void);
static void processinput(void);

void commandline_init(void) {
  LOG_INIT();
  current_pos = &current_line[0];
}


void commandline_addchar(char c) {
  if ( c == '\n' ) ; // ignore!
  else if ( c == '\r' ) processinput();
  else if ( c == 0x08 && current_pos > current_line ) current_pos--;
  else if ( current_pos < current_line + MAX_LINE )	*current_pos++ = c;
}


// let the parsing begin!


void processinput(void) {

  *current_pos = '\0';
  current_pos = &current_line[0];
  tokenize_pos = &current_line[0];
  additional_text = str_empty;

  // uppercase the input -> case insensitive parsing
  strupr(current_line);

  parse();
  
  // is changed by strtok_r
  current_pos = &current_line[0];
}

// begin terminal token parsers



static inline uint8_t is_digit (char d) {
  return d >= '0' && d <= '9';
}

static inline uint8_t is_number(char* s) {
  while ( *s != '\0') {
	if ( !is_digit(*s) ) return 0;
	s++;
  }
  return 1;
}

static inline char* parse_string(void) {
  char* t = strtok_r(NULL, separator, &current_pos);
  if ( t == '\0' ) {
	parse_fail = 1;
	additional_text = " failed to parse string; input empty";
  }
  return t;
}

static inline time_t parse_time(void) {

  char* time_pos;
  checked(char* token = parse_string()) 0;

  char* hs = strtok_r(token, ":", &time_pos);
  char* ms = strtok_r(NULL, ":", &time_pos);
  char* ss = strtok_r(NULL, ":", &time_pos);

  if ( !is_number(hs) || !is_number(ms) || !is_number(ss) ) {
	parse_fail = 1;
	additional_text = " time must be in hh:mm:ss format!";
	return 0;
  }

  // skip leading 0
  if ( *hs == '0') hs++;
  if ( *ms == '0') ms++;
  if ( *ss == '0') ss++;

  uint8_t h = atoi(hs);
  uint8_t m = atoi(ms);
  uint8_t s = atoi(ss);

  if ( h < 0 || h >= 24 || 
	   m < 0 || m >= 60 ||
	   s < 0 || s >= 60 ) {
	parse_fail = 1;
	additional_text = " invalid time format";
	return 0;
  }
  
  return time_from_hms(h, m, s);
}

static inline uint8_t parse_int(void) {
  char* t = strtok_r(NULL, separator, &current_pos);
  if ( t == '\0' ) parse_fail = 1;
  return atoi(t);
}


// begin production parsers


static void parse_set_time(void) {
  checked(time_t t = parse_time());

  ds1307_settime(time_get_h(t), time_get_m(t), time_get_s(t));
}

static void parse_set_timer(void) {

  checked(uint8_t id = parse_int());

  if ( id >= N_TIMESWITCHES ) {
	parse_fail = 1;
	return;
  }

  checked(time_t on = parse_time());
  checked(time_t off = parse_time());
  checked(uint8_t output  = parse_int());
  checked(uint8_t enabled  = parse_int());
  
  timeswitch_set(id, on, off, output, enabled);
}

static inline void parse_set_tempsetpoint(void) {
  checked(uint8_t value = parse_int());

  temp_setpoint = value;
  eeprom_write_byte(&ee_tempsetpoint, value);
}

static inline void parse_set_humiditysetpoint(void) {
  checked(uint8_t value = parse_int());

  humidity_setpoint = value;
  eeprom_write_byte(&ee_humiditysetpoint, value);
}

static inline void parse_set_output(void) {
  checked(uint8_t id = parse_int());

  id = 0;
  // set value
}

static inline void parse_get_timers(void) {
  char t_buf[TIMESWITCH_STR_SIZE];
  for ( uint8_t i = 0; i < N_TIMESWITCHES; i++ )
	puts( timeswitch_str(t_buf, i) );
}

#define TOKEN_IS(str) (strcmp(token, str)==0)


static void parse_set(void) {
  checked(char* token = parse_string());

  if (TOKEN_IS("TIME"))                  parse_set_time();
  else if (TOKEN_IS("TIMER"))            parse_set_timer();
  else if (TOKEN_IS("TEMPSETPOINT"))     parse_set_tempsetpoint();
  else if (TOKEN_IS("HUMIDITYSETPOINT")) parse_set_humiditysetpoint();
  else if (TOKEN_IS("OUTPUT"))           parse_set_output();
  else parse_fail = 1;
}


static void parse_get(void) {
  char t_buf[TIME_STR_SIZE];
  checked(char* token = parse_string());

  if (TOKEN_IS("TIME"))                  puts(time_str(t_buf, time_now()));
  else if (TOKEN_IS("TIMERS"))           parse_get_timers();
  else if (TOKEN_IS("TEMP"))             puts( itoa(temp, t_buf, 10) );
  else if (TOKEN_IS("TEMPSETPOINT"))     puts( itoa(temp_setpoint, t_buf, 10) );
  else if (TOKEN_IS("HUMIDITY"))         puts( itoa(humidity, t_buf, 10) );
  else if (TOKEN_IS("HUMIDITYSETPOINT")) puts( itoa(humidity_setpoint, t_buf, 10) );
  else if (TOKEN_IS("OUTPUTS"))          puts("stub-outputs");
  else if (TOKEN_IS("VERSION"))          puts(VERSION);
  else parse_fail = 1;
}


void parse(void) {

  parse_fail = 0;

  checked(char* token = parse_string());

  if ( *token == '\0' )        return;
  else if ( TOKEN_IS("SET"))   parse_set();
  else if ( TOKEN_IS("GET"))   parse_get();
  else if ( TOKEN_IS("HELLO")) ;  // nothing to do here, simply return str_ok
  else                         parse_fail = 1;

  // string fully consumed?
  if ( *current_pos != '\0' )  parse_fail = 1;
	
  if ( parse_fail ) printf(str_fail); 
  else printf(str_ok);

  puts(additional_text);
}
