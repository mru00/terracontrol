/* 
 * terrarium control
 * mru, november 2009
 *
 * portmap
 *
 */


enum {
  nPORTA,
  nPORTB,
  nPORTC,
  nPORTD
};


extern void portmap_init(void);
extern port_t portmap[];
