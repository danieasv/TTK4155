/*! @file
 * Implementation of adc driver header file.
 */
#ifndef ADC_DRIVER_H_
#define ADC_DRIVER_H_


int adc_init(void); ///< brief Function to initialize adc. 
uint8_t adc_read(int ch); /// Read adc value. @param ch ADC channel.



#endif /* ADC_DRIVER_H_ */