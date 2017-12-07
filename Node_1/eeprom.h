/** @file
This is the eeprom header file.
*/

#ifndef EEPROM_H_
#define EEPROM_H_

bool EEPROM_save_score(int8_t data);
unsigned char EEPROM_read(unsigned int address);
void EEPROM_write(unsigned int address, unsigned char data);


#endif /* EEPROM_H_ */