/*! @file
 * MPC driver for CAN controller. 
 * The file MPC2515.h contains constants that are specific to the MCP2515 controller. 
 */
#include "general_header.h"
#include "MCP2515.h"
#include "SPI_driver.h"
#include "mcp_driver.h"

/*!
 * \brief Reset MCP. Important to do a soft reset at startup.
 */
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

/*!
 * \brief Function to write to MPC register. 
 */
void MCP_write(uint8_t address, uint8_t data){
	SPI_ss_low(TRUE);
	SPI_transmit(MCP_WRITE);
	SPI_transmit(address);
	SPI_transmit(data);
	SPI_ss_low(FALSE);
}

/*!
 * \brief Read MPC status register.
 */
uint8_t MCP_readstatus(void){
	
	SPI_ss_low(TRUE);
	SPI_transmit(MCP_READ);
	SPI_transmit(MCP_CANINTF);
	uint8_t data = SPI_transmit(0xFF);
	SPI_ss_low(FALSE);
	return data;
}

/*!
 * \brief Write to MPC address register.
 * @param adress Write address. 
 */
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

/*!
 * \brief Read MPC register.
 */
uint8_t MCP_read(uint8_t address){
	SPI_ss_low(TRUE);
	SPI_transmit(MCP_READ);
	SPI_transmit(address);
	uint8_t data = SPI_transmit(0xFF);
	SPI_ss_low(FALSE);
	return data;
}

/*!
 * \brief Bitmodify function.
 * @param address 	Input address
 * @param mask 		Mask
 * @param data 		Data
 */
void MCP_bitmodify(uint8_t address, uint8_t mask, uint8_t data){
		SPI_ss_low(TRUE);
		SPI_transmit(MCP_BITMOD);
		SPI_transmit(address);
		SPI_transmit(mask);
		SPI_transmit(data);
		SPI_ss_low(FALSE);
}

/*!
 * \brief MCP init function
 * @param id 	Input sending ID.
 */
int MCP_init(uint8_t id){
	SPI_ss_low(TRUE);
	SPI_transmit(MCP_WRITE);
	SPI_transmit(MCP_RXB0SIDH);
	SPI_transmit(id >> 3);
	SPI_ss_low(FALSE);
	
	SPI_ss_low(TRUE);
	SPI_transmit(MCP_WRITE);
	SPI_transmit(MCP_RXB0SIDL); // BUFFER ID 
	SPI_transmit(id << 5);
	SPI_ss_low(FALSE);
	
// 	SPI_ss_low(TRUE);
// 	SPI_transmit(MCP_WRITE);
// 	SPI_transmit(MCP_RXF0SIDH);
// 	SPI_transmit(id >> 3);
// 	SPI_ss_low(FALSE);
// 	
// 	SPI_ss_low(TRUE);
// 	SPI_transmit(MCP_WRITE);
// 	SPI_transmit(MCP_RXF0SIDL); // FILTER ID
// 	SPI_transmit(id << 5);
// 	SPI_ss_low(FALSE);
// 	
// 	SPI_ss_low(TRUE);
// 	SPI_transmit(MCP_WRITE);
// 	SPI_transmit(MCP_RXM0SIDH);
// 	SPI_transmit(0xFF);
// 	SPI_ss_low(FALSE);
// 	
// 	SPI_ss_low(TRUE);
// 	SPI_transmit(MCP_WRITE);
// 	SPI_transmit(MCP_RXM0SIDL); // MASK, ENABLE ALL BITS
// 	SPI_transmit(0xE0);
// 	SPI_ss_low(FALSE);
	
	SPI_ss_low(TRUE);
	SPI_transmit(MCP_WRITE);
	SPI_transmit(MCP_TXB0DLC);
	SPI_transmit(0x01);			//Set 1 byte as default data length.
	SPI_ss_low(FALSE);
	
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