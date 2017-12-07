
#include "general_header_node2.h"
#include "MCP2515.h"
#include "SPI_driver_node2.h"
#include "mcp_driver_node2.h"


void MCP_reset(void){
	SPI_ss_low(TRUE);
	SPI_transmit(MCP_RESET);
	SPI_ss_low(FALSE);
	_delay_ms(100);
}

void MCP_rts(void){
	SPI_ss_low(TRUE);
	SPI_transmit(MCP_RTS_TX0);
	SPI_ss_low(FALSE);
}

void MCP_write(uint8_t address, uint8_t data){
	SPI_ss_low(TRUE);
	SPI_transmit(MCP_WRITE);
	SPI_transmit(address);
	SPI_transmit(data);
	SPI_ss_low(FALSE);
}

uint8_t MCP_readstatus(void){
	
	SPI_ss_low(TRUE);
	SPI_transmit(MCP_READ);
	SPI_transmit(MCP_CANINTF);
	uint8_t data = SPI_transmit(0xFF);
	SPI_ss_low(FALSE);
	return data;
}

void MCP_write_adress(uint8_t address){
	SPI_ss_low(TRUE);
	SPI_transmit(MCP_WRITE);
	SPI_transmit(address);
}

void MCP_write_register(uint8_t data){
	SPI_transmit(data);
}

void MCP_write_end(void){
	SPI_ss_low(FALSE);
}

uint8_t MCP_read(uint8_t address){
	SPI_ss_low(TRUE);
	SPI_transmit(MCP_READ);
	SPI_transmit(address);
	uint8_t data = SPI_transmit(0xFF);
	SPI_ss_low(FALSE);
	return data;
}

void MCP_bitmodify(uint8_t adress, uint8_t mask, uint8_t data){
		SPI_ss_low(TRUE);
		SPI_transmit(MCP_BITMOD);
		SPI_transmit(adress);
		SPI_transmit(mask);
		SPI_transmit(data);
		SPI_ss_low(FALSE);
}

int MCP_init(void){
	SPI_ss_low(TRUE);
	SPI_transmit(MCP_WRITE);
	SPI_transmit(MCP_RXB0SIDH);
	SPI_transmit(0x00);
	SPI_ss_low(FALSE);
	
	SPI_ss_low(TRUE);
	SPI_transmit(MCP_WRITE);
	SPI_transmit(MCP_RXB0SIDL);
	SPI_transmit(0xC0); // 
	SPI_ss_low(FALSE);
	
	SPI_ss_low(TRUE);
	SPI_transmit(MCP_WRITE);
	SPI_transmit(MCP_TXB0DLC);
	SPI_transmit(0x01);			//Set 1 byte as default data length.
	SPI_ss_low(FALSE);
	
// 	SPI_ss_low(TRUE);
// 	SPI_transmit(MCP_WRITE);
// 	SPI_transmit(MCP_TXB0SIDH);
// 	SPI_transmit(0x05);
// 	SPI_ss_low(FALSE);
// 	
// 	SPI_ss_low(TRUE);
// 	SPI_transmit(MCP_WRITE);
// 	SPI_transmit(MCP_TXB0SIDL);
// 	SPI_transmit(0x05);
// 	SPI_ss_low(FALSE);
// 	
	return 0;
}

/*
uint8_t MCP_read_RX_buffer(void){
	
	SPI_ss_low(TRUE);
	SPI_transmit(0x66); // Receive buffer 0
	uint8_t received_data = SPI_transmit(0xFF);
	SPI_ss_low(FALSE);

	return received_data;
}
*/
/*
void MCP_load_TX_buffer(uint8_t data){
	
		SPI_ss_low(TRUE);
		SPI_transmit(0x36); //Load TX buffer 0
		SPI_transmit(data);
		SPI_ss_low(FALSE);
	
}
*/