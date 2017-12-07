
#ifndef MCP_DRIVER_H_
#define MCP_DRIVER_H_

void MCP_reset(void);
void MCP_load_TX_buffer(uint8_t data);
uint8_t MCP_read_RX_buffer(void);
void MCP_bitmodify(uint8_t adress, uint8_t mask, uint8_t data);
void MCP_write(uint8_t address, uint8_t data);
void MCP_write_adress(uint8_t address);
void MCP_write_register(uint8_t data);
void MCP_write_end(void);
uint8_t MCP_read(uint8_t address);
void MCP_rts(void);
int MCP_init(void);
uint8_t MCP_readstatus(void);

#endif /* MCP_DRIVER_H_ */