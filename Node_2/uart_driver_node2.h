
#ifndef UART_DRIVER_H_
#define UART_DRIVER_H_

int uart_init(unsigned baud);
int uart_transmit(unsigned char data);
unsigned char uart_receive(void);
void test_uart(void);

#endif /* UART_DRIVER_H_ */