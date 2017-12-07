/*! @file
 * Can driver header file
 */

#ifndef CAN_DRIVER_H_
#define CAN_DRIVER_H_

//void CAN_reset(void);
int CAN_init(uint16_t mode, uint8_t id);
uint8_t CAN_loopback(uint8_t data);
void CAN_transfer(uint8_t data);
void CAN_transfer_2(uint8_t data1, uint8_t data2);
uint8_t CAN_busywait_reveive(void);
uint8_t CAN_check_reveive(void);
//This function is used for sending CAN messages in game. Arbritary message length and id.
void CAN_send(uint8_t id, int data_byte, int* data);

typedef struct can_msg_type 
{
	uint8_t id;
	uint8_t data;	
} ;


#endif /* CAN_DRIVER_H_ */