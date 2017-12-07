/** @file
 * This is the eeprom file used to save highschore and brightness.
 */
#include "general_header.h"

/*!
  * \brief Write data to EEPROM address
  * @param address Address to data
  * @param data Data to store
  */
void EEPROM_write(unsigned int address, unsigned char data){
	cli(); //disable interupts
	
	EEAR = address;	//Write to address
	EEDR = data;	//Data to write.
	
	/* start EEPROM write */
	EECR |= (1<<EEMWE); 
	EECR |= (1<<EEWE);	
	
	sei(); // Enable interupts	
}

/*!
  * \brief Read value from EEPROM address.
  * @param address Address to data
  */
unsigned char EEPROM_read(unsigned int address){
	
	while(EECR &(1 << EEWE)); 	/// Wait for complete of previous write
	EEAR = address;
	EECR |= (1<<EERE); 			/// Start eeprom read by writing EERE
	return EEDR;				/// Return data from register
}

/*!
  * \brief Function to save highscore
  * @data value to store
  */
bool EEPROM_save_score(int8_t data){
	uint8_t score_list[5];
	uint8_t temp_index = 4;
	uint8_t value;
	
	for(int i = 4; i>=0; i--){
		value = EEPROM_read(i);
		if (data > value){
			score_list[temp_index] = value;
			if (i == 0){
				EEPROM_write(0,data); // Insert max value
				//Reorder values
				while(temp_index < 4){
					EEPROM_write(temp_index +1, score_list[temp_index]);
					temp_index++;
				}
				return true;
			}
			temp_index--;
		}
		else{
			score_list[temp_index] = data;
			//Reorder values
			while(temp_index < 4){
				EEPROM_write(temp_index +1, score_list[temp_index]);
				temp_index++;
			}
			return true;
		}
	}
	return true;
}