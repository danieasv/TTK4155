
#ifndef UART_DRIVER_H_
#define UART_DRIVER_H_

int uart_init(unsigned baud);
int uart_transmit(unsigned char data);
unsigned char uart_receive(void);
void test_uart(void);

static FILE uart_out = FDEV_SETUP_STREAM(uart_transmit, NULL, _FDEV_SETUP_WRITE);
static FILE uart_in = FDEV_SETUP_STREAM(NULL, uart_receive, _FDEV_SETUP_READ);

#define UART (&uart_out)

#endif /* UART_DRIVER_H_ */