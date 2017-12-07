
#ifndef SPI_driver_H_
#define SPI_driver_H_

int SPI_master_init(void);
uint8_t SPI_transmit(uint8_t data);
void SPI_ss_low(int mode);

#endif /* SPI_driver_H_ */