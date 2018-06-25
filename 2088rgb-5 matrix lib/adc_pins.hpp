#ifndef ADCPIN_HPP
#define ADCPIN_HPP

#include "hwlib.hpp"
#include "sam.h"

class adc_pins{
private:
	uint_fast16_t enabledChannels; // variable to store which channels are enabled
	int highestChannel; // variable to store which channel the highest channel. This channel will be converted last
public:
	adc_pins(): enabledChannels(0), highestChannel(-1){
		PMC -> PMC_WPMR = (0x504D43 << 8) | 1; // enable writing to PMC registers
		PMC -> PMC_PCER1 = 1 << 5; // activate the ADC clock
		
		ADC -> ADC_WPMR = (0x414443 << 8) | 1; // enable writing to the ADC registers
		ADC -> ADC_MR = 0x1E3F0011; // all settings combined in one hexadecimal number
		ADC -> ADC_IDR = 0xFFFFFFFE; // disable all interrupts except the "end of conversion interrupt" on all channels
		ADC -> ADC_IER = 1; // enable the "end of conversion interrupt" on all channels
		ADC -> ADC_CGR = 0x55555555; // set all gains to 1
		ADC -> ADC_COR = 0; // set offset to 0 on all channels
	}
	
	void enableChannel(int channel);
	
	void disableChannel(int channel);
	
	int startConversion(int channel = -1);
	
	int getResult(int channel);
	
	uint_fast16_t getEnabledChannels();
};

#endif
