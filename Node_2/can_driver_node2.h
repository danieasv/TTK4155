
#ifndef CAN_DRIVER_H_
#define CAN_DRIVER_H_

//void CAN_reset(void);
int CAN_init(uint16_t mode);
uint8_t CAN_loopback(uint8_t data);
void CAN_transfer(uint8_t data);
void CAN_receive(int8_t *receive_array);
// typedef	 struct {
// 	
// 	
// 				}
// 				 can_TX_buffer_t;

#endif /* CAN_DRIVER_H_ */