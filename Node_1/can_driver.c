/*! @file
 * Implementation of high level CAN bus controller.
 */
#include "general_header.h"
#include "spi_driver.h"
#include "can_driver.h"
#include "MCP2515.h"
#include "mcp_driver.h"

volatile bool can_wait_for_receive;  /*!< Can variable to check if ready to receive.


/*!
 * \brief Initialize CAN controller and MCP. 
 * @param mode 	Choose between MODE_NORMAL or MODE_LOOPBACK
 * @param id 	Initialize with fixed message ID.
 */
int CAN_init(uint16_t mode, uint8_t id){
	
	cli();
	clear_bit(EMCUCR,ISC2); /*! Trigger interrupt on falling edge on INT2.*/ 
	set_bit(GICR,INT2);		/*! Enable interrupt on INT2 */
	sei();
	
	MCP_init(id); ///< Set ID
	
	MCP_bitmodify(MCP_CANCTRL, MODE_MASK, mode); ///< Set mode 
	
	#ifdef UART_DEBUG
 	if ((MCP_read(MCP_CANSTAT) & 0xE0) == MODE_LOOPBACK)
	{
 		printf("\n\r MCU MODE LOOPBACK\n");
 	}
 	else if ((MCP_read(MCP_CANSTAT) & 0xE0) == MODE_NORMAL) {
 		printf("\n\rMCU MODE NORMAL\n");
 	}
	#endif /*UART_DEBUG */

	return 0;
}

/*
 * \brief Send message in Loopback mode.
 * @param data Data to send in loopback mode.
 */
uint8_t CAN_loopback(uint8_t data){
	
#ifdef UART_DEBUG
	printf("\n\r CAN LOOPBACK MODE ");
	printf("\n\r\t DATA SENDT: \t 0x%02x", data);
#endif /* UART_DEBUG */

	/*! SET ARBRITARY VALUES FOR ID AND DATA LENGTH */
	MCP_write(MCP_TXB0SIDH, 0x05);
	MCP_write(MCP_TXB0SIDL, 0x80);
	MCP_write(MCP_TXB0DLC, 0x01);
	
	MCP_write(MCP_TXB0D0, data); //!< Load data into TX0 buffer
	MCP_rts();
	
	/*! WAIT FOR RX BUFFER 0 INTERUPT */
	while(!(MCP_readstatus() & 0x1)){
		_delay_ms(1);
		//printf("\n\r-- Waiting for RXB0IF --"); //NOT SURE ABOUT REGISTER NAME
	}
	
	uint8_t received_data = MCP_read(MCP_RXB0D0); //read RX0 data buffer.
	
	//printf("\n\r\t DATA RECEIVED:\t 0x%02x\n", received_data);
	
	return received_data;
}

/*!
 * Send message on can bus.
 * @param data Data to send on bus
 */
void CAN_transfer(uint8_t data){
	
	//printf("\n\r CAN TRANSFER MODE ");
	//printf("\n\r\t DATA SENDT: \t 0x%02x", data);
	
	//SET ARBRITARY VALUES FOR ID AND DATA LENGTH
	MCP_write(MCP_TXB0SIDH, 0x00);
	MCP_write(MCP_TXB0SIDL, 0x80);
	MCP_write(MCP_TXB0DLC, 0x01); //8bit
	
	MCP_write(MCP_TXB0D0, data); //Load data into TX0 buffer
	MCP_rts();	
}

/*!
 * Send message on can bus.
 * @param id CAN ID to send with
 * @param data_byte Number of bytes (from 1 to 8)
 * @param data Pointer with data to send.
 */
void CAN_send(uint8_t id, int data_byte, int* data)
{
	if(data_byte < 0 || data_byte > 8)
	{
		printf("Wrong number of data bytes: %u", data_byte);
		return;
	}
	while((MCP_read(MCP_TXB0CTRL & (1<<MCP_TXREQ)))); // Wait for buffer to be cleared.
	MCP_write(MCP_TXB0DLC, data_byte);			
	MCP_write(MCP_TXB0SIDL, id);
	for(int i = 0; i < data_byte; i++)
	{
		MCP_write(MCP_TXB0D0 +i, data[i]);
	}
	MCP_rts(); //!< Ready to send function.
}

void CAN_transfer_2(uint8_t data1, uint8_t data2){
	/*! SET ARBRITARY VALUES FOR ID AND DATA LENGTH */
	MCP_write(MCP_TXB0SIDH, 0x00);
	MCP_write(MCP_TXB0SIDL, 0x80);
	MCP_write(MCP_TXB0DLC, 0x02); // 2 bytes
	
	MCP_write(MCP_TXB0D0, data1); //!< Load data into TX0 buffer
	MCP_write(MCP_TXB0D1, data2); //!< Load data into TX0 buffer
	MCP_rts();
}



/*! CAN receive function */
uint8_t CAN_busywait_reveive(void){
	
	can_wait_for_receive = true;
	
	/*!WAIT FOR RX BUFFER 0 INTERUPT */
	while(!(MCP_readstatus() & MCP_RX0IF)){
		_delay_ms(10);
		printf("WAITING \n\r");
	}

	uint8_t received_data = MCP_read(MCP_RXB0D0); ///read RX0 data buffer.
	
	printf("CAN received data: %i  \r\n", received_data);
	
	MCP_bitmodify(MCP_CANINTF, MCP_RX0IF, 0x00); ///turn off the interrupt flag after reading
	
	return received_data;
}

uint8_t CAN_check_reveive(void){

	uint8_t received_data = 0;
	//WAIT FOR RX BUFFER 0 INTERUPT
	
	if((MCP_readstatus() & MCP_RX0IF)){
		received_data = MCP_read(MCP_RXB0D0);
	}
	
	MCP_bitmodify(MCP_CANINTF, MCP_RX0IF, 0x00); //turn off the interrupt flag after reading
	
	//printf("CAN received data: %i  \r\n", received_data);
	
	return received_data;
}


//! CAN message interupt on receive. 
ISR(INT2_vect){
	can_wait_for_receive = false;
	cli();
	set_bit(GIFR,INTF2); // Clear interupt flag.
	sei();
}
