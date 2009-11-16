
/* 
 * terrarium control
 * mru, november 2009
 *
 * TLV5620 8bit serial D/A converter
 */



// the DAC - id's
enum {
  TLV_DACA,
  TLV_DACB,
  TLV_DACC,
  TLV_DACD
};


extern void tlv_init(void);


extern void tlv_setup_port(const uint8_t po_load, const uint8_t pi_load, 
						   const uint8_t po_clk, const uint8_t pi_clk,
						   const uint8_t po_data, const uint8_t pi_data,
						   const uint8_t po_ldac, const uint8_t pi_ldac);

extern void tlv_set(const uint8_t id, const uint8_t value);

