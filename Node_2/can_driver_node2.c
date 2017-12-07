#include "general_header_node2.h"
#include "spi_driver_node2.h"
#include "mcp_driver_node2.h"
#include "can_driver_node2.h"
#include "MCP2515.h"


int CAN_init(uint16_t mode){
	
	MCP_reset();
	MCP_bitmodify(MCP_CANCTRL, MODE_MASK, MODE_CONFIG); //set config mode to access filters
	if ((MCP_read(MCP_CANSTAT) & 0xE0) == 0x80){
		MCP_bitmodify(MCP_RXB0CTRL, 0x60, 0x60);
		printf("\n\r MCU MODE CONFIG. FILTERS DISABLED.\n");
	} 
	else{
		printf("\n\rERROR: MODE IS NOT CONFIG. FILTERS NOT DISABLED.\n");
	}
	
	MCP_bitmodify(MCP_CANCTRL, MODE_MASK, mode); //set mode
	
	return 0;
}


// CAN_load_TX_buffer(struct buffer)
// 	.id  
// 	.data
// 	.length
// 	.buffer
// 	
// CAN_send_message()
// 	MCP_load_TX_buffer(data)


uint8_t CAN_loopback(uint8_t data){

	printf("\n\r CAN LOOPBACK MODE ");
	printf("\n\r\t DATA SENDT: \t 0x%02x", data);
	
	//SET ARBRITARY VALUES FOR ID AND DATA LENGTH
	MCP_write(MCP_TXB0SIDH, 0x05);
	MCP_write(MCP_TXB0SIDL, 0x80);
	MCP_write(MCP_TXB0DLC, 0x01);
	
	MCP_write(MCP_TXB0D0, data); //Load data into TX0 buffer
	MCP_rts();
	
	//WAIT FOR RX BUFFER 0 INTERUPT
	while(!(MCP_readstatus() & 0x1)){
		_delay_ms(1);
		printf("\n\r-- Waiting for RXB0IF --"); //NOT SURE ABOUT REGISTER NAME
	}
	
	uint8_t received_data = MCP_read(MCP_RXB0D0); //read RX0 data buffer.
	
	printf("\n\r\t DATA RECEIVED:\t 0x%02x\n", received_data);
	
	return received_data;
}


void CAN_transfer(uint8_t data){
	
	printf("\n\r CAN TRANSFER MODE ");
	printf("\n\r\t DATA SENDT: \t 0x%02x", data);
	
	//SET ARBRITARY VALUES FOR ID, AND DATA LENGTH 1 BYTE
	MCP_write(MCP_TXB0SIDH, 0x00);
	MCP_write(MCP_TXB0SIDL, 0x20);
	MCP_write(MCP_TXB0DLC, 0x01); //8bit
	
	MCP_write(MCP_TXB0D0, data); //Load data into TX0 buffer
	MCP_rts();
}

void CAN_receive(int8_t *receive_array){

	//WAIT FOR RX BUFFER 0 INTERUPT
	while(!(MCP_readstatus() & MCP_RX0IF)){
		_delay_us(10);
		//printf("\r-- Waiting for RXB0IF --\n");
	}
	
	receive_array[0] = MCP_read(MCP_RXB0D0); //read RX0 data buffer.
	receive_array[1] = MCP_read(MCP_RXB0D0 + 1); //read RX1 data buffer.
	receive_array[2] = MCP_read(MCP_RXB0D0 + 2); //read RX2 data buffer.
	receive_array[3] = MCP_read(MCP_RXB0D0 + 3); //read RX3 data buffer.
	
	MCP_bitmodify(MCP_CANINTF, MCP_RX0IF, 0x00); //turn off the interrupt flag after reading
	
}