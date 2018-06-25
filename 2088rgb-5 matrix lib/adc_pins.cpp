#include "hwlib.hpp"

#include "adc_pins.hpp"

void adc_pins::enableChannel(int channel){
	enabledChannels |= (1 << channel);
	ADC -> ADC_CHER = enabledChannels;
	if(highestChannel < channel){
		highestChannel = channel;
	}
}

void adc_pins::disableChannel(int channel){
	enabledChannels &= (~(1<<channel));
	ADC -> ADC_CHDR = enabledChannels;
	
	if(highestChannel <= channel){
		for(int i=11; i>=0; i--){
			if((enabledChannels >> i) & 1){
				highestChannel = i;
				return;
			}
		}
	}
}

int adc_pins::startConversion(int channel){
	// clear the ADC_ISR by reading all ADC_CDR registers
	volatile int tmp; // volatile int to make sure that the compiler doesn't remove the reading of the registers
	for(int i=0; i<16; i++){
		tmp = ADC -> ADC_CDR[i] & 0xFFF;
	}
	
	// start the conversion
	ADC -> ADC_CR = 2;
	
	// check if conversion is complete.
	/*tmp = 1;
	while(tmp != 0){
		tmp = ADC -> ADC_ISR & 0xFFF;
		tmp >>= highestChannel;
		tmp &= 1;
		hwlib::wait_us(10);
	}*/
	hwlib::wait_us(100);
	
	// if a channel has been given, return the result of that channel;
	if(channel != -1){
		int returnF = ADC -> ADC_CDR[channel] & 0xFFF;
		return returnF;
	}
	return 0;
}

int adc_pins::getResult(int channel){
	return ADC -> ADC_CDR[channel] & 0xFFF;
}

uint_fast16_t adc_pins::getEnabledChannels(){
	return enabledChannels;
}
