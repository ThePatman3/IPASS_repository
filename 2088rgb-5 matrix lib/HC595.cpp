#include "hwlib.hpp"
#include "HC595.hpp"

hc595::hc595(hwlib::pin_out & _SI, hwlib::pin_out & _SCK, hwlib::pin_out & _RCK, hwlib::pin_out & _SCLR, hwlib::pin_out & _G):
	SI(_SI), SCK(_SCK), RCK(_RCK), SCLR(_SCLR), G(_G), waitTime_us(1), currentData(0)
	{
	SI.set(false);
	SCK.set(false);
	RCK.set(false);
	SCLR.set(true);
	G.set(false);
	clear();
}

void hc595::writeData(uint_fast8_t data, bool direction){ // when direction == true, the lsb will be placed at Qh and the msb will be placed at Qa.
	bool bit = 0;
	if(direction){
		for(int i = 0; i < 8; i++){
			bit = (data >> i) & 1;
			SI.set(bit);
			hwlib::wait_us(waitTime_us);
			SCK.set(true);
			hwlib::wait_us(waitTime_us);
			SCK.set(false);
		}
	}else{
		for(int i = 7; i >= 0; i--){
			bit = (data >> i) & 1;
			SI.set(bit);
			hwlib::wait_us(waitTime_us);
			SCK.set(true);
			hwlib::wait_us(waitTime_us);
			SCK.set(false);
		}
	}
	RCK.set(true);
	hwlib::wait_us(waitTime_us);
	RCK.set(false);
	SI.set(false);
	currentData = data;
}

void hc595::shiftData(bool bit){
	SI.set(bit);
	hwlib::wait_us(waitTime_us);
	SCK.set(true);
	hwlib::wait_us(waitTime_us);
	SCK.set(false);
	RCK.set(true);
	hwlib::wait_us(waitTime_us);
	RCK.set(false);
	SI.set(false);
	currentData = (currentData >> 1) & ~(1 << 7);
	currentData = currentData ^ (bit << 7);
}

void hc595::clear(){
	SCLR.set(false);
	hwlib::wait_us(waitTime_us);
	RCK.set(true);
	hwlib::wait_us(waitTime_us);
	SCLR.set(true);
	RCK.set(false);
	currentData = 0;
}

void hc595::enableOutput(bool enable){
	G.set(!enable);
}

uint_fast8_t hc595::get_currentData(){
	return currentData;
}
