
#include "general_header_node2.h"
#include "uart_driver_node2.h"

int uart_init(uint16_t baud){
	//Set baud rate
	uint16_t ubrr = F_CPU / 16 / baud - 1;
	UBRR0H = (unsigned char) (ubrr >> 8);
	UBRR0L = (unsigned char) ubrr;

	//Enable receiver and transmitter
	UCSR0B = (1 << RXEN0 ) | (1 << TXEN0);
	
	//Frame format, 8 data & 2 stop bit
	fdevopen(uart_transmit,uart_receive);
	UCSR0C =  (1 << USBS0) | (1 << UCSZ00) | (1 << UCSZ01);
	return 0;
}

int uart_transmit(unsigned char data){
	//wait for empty buffer
	while(!(UCSR0A & (1 << UDRE0)));
	//Send data
	UDR0 = data; 
	return 0; 
}

unsigned char uart_receive(void){
	//Wait for data
	while(!(UCSR0A & (1 << RXC0)));
	//Get and return received data from buffer
	return UDR0;
}


void test_uart(void){
	char input_str[20];
	scanf("%s", input_str);
	printf("Entered text: %s\n", input_str);
}