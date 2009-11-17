/* 
 * terrarium control
 * mru, november 2009
 *
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
static char separator[] = " ";

static void parse(void);

void commandline_init(void) {
  LOG_INIT();
  current_pos = &current_line[0];
}

void commandline_addchar(char c) {
  if ( current_pos < current_line + MAX_LINE )
	*current_pos++ = c;
}

void commandline_processline(void) {

  *current_pos = '\0';
  current_pos = &current_line[0];
  tokenize_pos = &current_line[0];

  strupr(current_line);

  puts(current_line);


  parse();
  
  // is changed by strtok_r
  current_pos = &current_line[0];
}




static time_t parse_time(void) {

  time_t h, m ,s;
  
  char* parts[3];
  int i;

  for (i = 0; i < 3; i ++ ) {
	parts[0] = strtok_r(NULL, ":", &current_pos);
	printf("part %d: >%s< = %d\r\n", i, parts[0], atoi(parts[0]) );
  }

  h = 3600UL * atoi(parts[0]) ;
  m = 60UL * atoi(parts[1]) ;
  s = atoi(parts[2]);

  printf(" h+m+s %lu %lu %lu\r\n", h, m, s );

  return (h+m+s);
}


static void parse_set(void) {

  puts("S");
  char* token = strtok_r(NULL, separator, &current_pos);

  if (strcmp(token, "TIME") == 0) {
	time_t t = parse_time();
	printf("ST time: \r\n" TIME_PRINTF_MASK, TIME_PRINTF_DATA(t) );

  }
  else {
	puts("F");
  }
}


void parse(void) {

  char* token = strtok_r(current_line, separator, &current_pos);

  if ( *token == '\0' ) return;
  else if ( strcmp(token, "SET") == 0 ) parse_set();
  else if ( strcmp(token, "GET") == 0 ) puts("G");
  else puts("F");
}
