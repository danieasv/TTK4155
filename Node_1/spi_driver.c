
#include "general_header.h"
#include "spi_driver.h"

int SPI_master_init(void){
	/* Set MOSI and SCK output, all others input. Force SPI MODE 0 */
	set_bit(DDRB,PB4);	// Set SS as output
	set_bit(DDRB,PB5);	// Set MOSI as output
	clear_bit(DDRB,PB6);	//Set MISO as input
	set_bit(DDRB,PB7);	// Set SCK as output
	set_bit(SPCR,MSTR);		// Set master node
	clear_bit(SPCR,CPOL);	// CPOL = 0
	clear_bit(SPCR,CPHA);	// CPHA = 0
	set_bit(SPCR,SPR0);
	set_bit(SPCR,SPE);		// Enable SPI
	set_bit(PORTB,PINB4);	// Set SS high
	
	return 0;
}


uint8_t SPI_transmit(uint8_t data){
	
	SPDR = data;
	while(!(SPSR & (1 << SPIF)));
	uint8_t received_data = SPDR;
	return received_data;
	

}


void SPI_ss_low(int mode){
	if (mode){
		clear_bit(PORTB, PB4);
	} 
	else{
		set_bit(PORTB,PB4);
	}
}





