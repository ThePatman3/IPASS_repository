#ifndef HC595LIB_HPP
#define HC595LIB_HPP

#include "hwlib.hpp"

class hc595{
private:
	hwlib::pin_out & SI;
	hwlib::pin_out & SCK;
	hwlib::pin_out & RCK;
	hwlib::pin_out & SCLR;
	hwlib::pin_out & G;
	int waitTime_ms;
	uint_fast8_t currentData;
	
public:
	hc595(hwlib::pin_out & _SI, hwlib::pin_out & _SCK, hwlib::pin_out & _RCK, hwlib::pin_out & _SCLR = hwlib::pin_out_dummy, hwlib::pin_out & _G = hwlib::pin_out_dummy);
	void writeData(uint_fast8_t data);
	void shiftData(bool bit = 0);
	void clear();
	void enableOutput(bool enable);
	
	uint_fast8_t get_currentData();
};

#endif