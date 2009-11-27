/* 
 * terrarium control
 * mru, november 2009
 *
 * serial commandline interface
 */

#include <avr/io.h>
#include <string.h>
#include <avr/pgmspace.h>
#include "common.h"


#define MAX_LINE 40

#define TOKEN_IS(str) (strcmp_P(token, PSTR(str))==0)

static char current_line[MAX_LINE];
static char* current_pos;
static char* tokenize_pos;
static const char* additional_text = NULL;

static const char separator[] = " ";
static const char str_fail[] = "FAIL";
static const char str_ok[] = "OK";


static uint8_t parse_fail = 0;
static uint8_t current_token = 0;


#ifdef COMMANDLINE_DEBUG
#  define checked(stmt)  stmt; if(parse_fail) return
#  define checked_r(stmt, r)  stmt; if(parse_fail) return r
#else 
#  define checked(stmt)  stmt
#  define checked_r(stmt, r)  stmt
#endif


static void parse(void);
static void processinput(void);

void commandline_init(void) {
  LOG_INIT();
  current_pos = &current_line[0];
  LOG_INIT_EXIT();
}

void commandline_addchar(char c) {
  if ( c == '\n' )      ; // ignore!
  else if ( c == '\r' ) processinput();
  else if ( c == 0x08 && current_pos > current_line ) *current_pos-- = '\0';
  else if ( current_pos < current_line + MAX_LINE )	*current_pos++ = c;
}


// let the parsing begin!


void processinput(void) {

  *current_pos = '\0';
  current_pos = &current_line[0];
  tokenize_pos = &current_line[0];
  additional_text = PSTR("");

#ifdef COMMANDLINE_DEBUG
  current_token = 0;
#endif

  // uppercase the input -> case insensitive parsing
  strupr(current_line); // cost: 22 bytes

  parse();
  
  // is changed by strtok_r
  current_pos = &current_line[0];
}

// begin terminal token parsers


static char* parse_string(void) {
  char* t = strtok_r(NULL, separator, &current_pos);

  current_token ++;
#ifdef COMMANDLINE_DEBUG
  if ( t == '\0' ) {
	parse_fail = 1;
	additional_text = PSTR(" failed to parse string; input empty");
  }
#endif
  return t;
}

static time_t parse_time(void) {

  char* time_pos;
  checked_r(char* token = parse_string(), 0);

  char* hs = strtok_r(token, ":", &time_pos);
  char* ms = strtok_r(NULL, ":", &time_pos);
  char* ss = strtok_r(NULL, ":", &time_pos);

#ifdef COMMANDLINE_DEBUG
  if ( !is_number(hs) || !is_number(ms) || !is_number(ss) ) {
	parse_fail = 1;
	additional_text = PSTR(" time must be in hh:mm:ss format!");
	return 0;
  }
#endif


  uint8_t h = atoi8(hs);
  uint8_t m = atoi8(ms);
  uint8_t s = atoi8(ss);

#ifdef COMMANDLINE_DEBUG
  if ( h >= 24 || m >= 60 || s >= 60 ) {
	parse_fail = 1;
	additional_text = PSTR(" invalid time format");
	return 0;
  }
#endif
  
  return time_from_hms(h, m, s);
}


static date_t parse_date(void) {

  char* date_pos;
  checked_r(char* token = parse_string(), 0);

  char* ds = strtok_r(token, ".", &date_pos);
  char* ms = strtok_r(NULL, ".", &date_pos);
  char* ys = strtok_r(NULL, ".", &date_pos);

#ifdef COMMANDLINE_DEBUG
  if ( !is_number(ds) || !is_number(ms) || !is_number(ys) ) {
	parse_fail = 1;
	additional_text = PSTR(" date must be in dd.mm.yy format!");
	return 0;
  }
#endif

  uint8_t d = atoi8(ds);
  uint8_t m = atoi8(ms);
  uint8_t y = atoi8(ys);

#ifdef COMMANDLINE_DEBUG
  if ( d > 31 || m > 12 || y > 99 ) {
	parse_fail = 1;
	additional_text = PSTR(" invalid date format");
	return 0;
  }
#endif
  
  return date_from_dmy(d, m, y);
}


static uint8_t parse_int(void) {
  checked_r(char* token = parse_string(), 0);

#ifdef COMMANDLINE_DEBUG
  if ( !is_number(token) ) {
	parse_fail = 1;
	additional_text = PSTR(" parse_int failed");
  }
#endif

  return atoi8(token);
}


// begin production parsers
static void parse_set_time(void) {
  checked(time_t t = parse_time());
  ds1307_settime(time_get_h(t), time_get_m(t), time_get_s(t));
}

static void parse_set_date(void) {
  checked(date_t t = parse_date());
  ds1307_setdate(date_get_d(t), date_get_m(t), date_get_y(t));
}

static void parse_set_timer(void) {

  checked(uint8_t id = parse_int());

#ifdef COMMANDLINE_DEBUG
  if ( id >= N_TIMESWITCHES ) {
	parse_fail = 1;
	return;
  }
#endif

  checked(time_t on = parse_time());
  checked(time_t off = parse_time());
  checked(uint8_t output  = parse_int());
  checked(uint8_t enabled  = parse_int());
  
  timeswitch_set(id, on, off, output, enabled);
}

static void parse_set_tempsetpoint(void) {
  int t[2];

  checked(t[DAY] = parse_int());
  checked(t[NIGHT] = parse_int());

  for (int i = 0; i < 2; i ++ ) {
	temp_setpoint[i] = t[i];
	eeprom_write_byte(&ee_tempsetpoint[i], temp_setpoint[i]);
  }
}

static void parse_set_humiditysetpoint(void) {

  int h[2];

  checked(h[DAY] = parse_int());
  checked(h[NIGHT] = parse_int());

  for (int i = 0; i < 2; i ++ ) {
	humidity_setpoint[i] = h[i];
	eeprom_write_byte(&ee_humiditysetpoint[i], humidity_setpoint[i]);
  }
}

static void parse_set_output(void) {
  checked(uint8_t id = parse_int());

  id = 0;
  // set value
}

static void parse_set_daytime(void) {
  time_t t[2];
  checked(t[DAYTIME_BEGIN] = parse_time());
  checked(t[DAYTIME_END] = parse_time());

  for (int i = 0; i < 2; i ++ ) {
	daytime[i] = t[i];
	eeprom_write_block((const void*) (&daytime[i]), &ee_daytime[i], sizeof(time_t));
  }
}

static void parse_get_timers(void) {
  for ( uint8_t i = 0; i < N_TIMESWITCHES; i++ ) {
	timeswitch_print(i);
	uart_puts(NEWLINE);
  }
}

static void parse_get_time(void) {
  time_print(time_now()); 
  uart_puts(NEWLINE);
}

static void parse_get_date(void) {
  date_print(date_now()); 
  uart_puts(NEWLINE);
}

static void parse_get_outputs(void) {
  for ( uint8_t i = OUTPUT_FIRST; i < OUTPUT_LAST; i ++ ) {
	portmap_print_output(i);
	uart_puts(NEWLINE);
  }
}

static void parse_get_daytime(void) {
  time_daytime_print();
  uart_puts(NEWLINE);
}



static void parse_get_temp(void) {
  char buf[4];
  uart_puts(itoa8(temp, buf));
  uart_puts(NEWLINE);
}

static void parse_get_tempsetpoint(void) {
  char buf[4];
  uart_puts(itoa8(temp_setpoint[DAY], buf));
  uart_puts(" ");
  uart_puts(itoa8(temp_setpoint[NIGHT], buf));
  uart_puts(NEWLINE);
}

static void parse_get_humidity(void) {
  char buf[4];
  uart_puts(itoa8(humidity, buf));
  uart_puts(NEWLINE);
}

static void parse_get_humiditysetpoint(void) {
  char buf[4];
  uart_puts(itoa8(humidity_setpoint[DAY], buf));
  uart_puts(" ");
  uart_puts(itoa8(humidity_setpoint[NIGHT], buf));
  uart_puts(NEWLINE);
}




// top level parsers:


static void parse_set(void) {
  checked(char* token = parse_string());

  if (TOKEN_IS("TIME"))                  parse_set_time();
  else if (TOKEN_IS("DATE"))             parse_set_date();
  else if (TOKEN_IS("DAYTIME"))          parse_set_daytime();
  else if (TOKEN_IS("TIMER"))            parse_set_timer();
  else if (TOKEN_IS("TEMPSETPOINT"))     parse_set_tempsetpoint();
  else if (TOKEN_IS("HUMIDITYSETPOINT")) parse_set_humiditysetpoint();
  else if (TOKEN_IS("OUTPUT"))           parse_set_output();
  else  { parse_fail = 1; additional_text = PSTR(" UNKNOWN COMMAND"); }
}


static void parse_get(void) {
  checked(char* token = parse_string());

  if (TOKEN_IS("TIME"))                  parse_get_time();
  else if (TOKEN_IS("DATE"))             parse_get_date();
  else if (TOKEN_IS("DAYTIME"))          parse_get_daytime();
  else if (TOKEN_IS("TIMERS"))           parse_get_timers();
  else if (TOKEN_IS("TEMP"))             parse_get_temp();
  else if (TOKEN_IS("TEMPSETPOINT"))     parse_get_tempsetpoint();
  else if (TOKEN_IS("HUMIDITY"))         parse_get_humidity();
  else if (TOKEN_IS("HUMIDITYSETPOINT")) parse_get_humiditysetpoint();
  else if (TOKEN_IS("OUTPUTS"))          parse_get_outputs();
  else if (TOKEN_IS("VERSION"))          uart_puts("TerraControl " VERSION ", mru 2009" );
  else  { parse_fail = 1; additional_text = PSTR(" UNKNOWN COMMAND"); }
}

// parser start symbol

void parse(void) {

  parse_fail = 0;

  checked(char* token = parse_string());

  if ( *token == '\0' )           return;
  else if ( TOKEN_IS("SET"))      parse_set();
  else if ( TOKEN_IS("GET"))      parse_get();
  else if ( TOKEN_IS("HELLO"))    additional_text = PSTR(" zerwas");
  else if ( TOKEN_IS("SELFTEST")) selftest_perform();
  else                            { parse_fail = 1; additional_text = PSTR(" UNKNOWN COMMAND"); }

#ifdef COMMANDLINE_DEBUG
  // string fully consumed?
  if ( *current_pos != '\0' )  {
	parse_fail = 1;
	additional_text = PSTR(" too much input");
  }
#endif

  if ( parse_fail ) uart_puts(str_fail); 
  else uart_puts(str_ok);

  uart_puts_p(additional_text);
  uart_puts(NEWLINE);
}
