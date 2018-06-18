#include "hwlib.hpp"

#include "HC595.hpp"

int main(){
	
	// kill the watchdog
	WDT->WDT_MR = WDT_MR_WDDIS;
	
	hwlib::target::pin_out si = hwlib::target::pin_out(2, 22); // D8
	hwlib::target::pin_out sck = hwlib::target::pin_out(2, 23); // D7
	hwlib::target::pin_out rck = hwlib::target::pin_out(2, 25); // D5
	hwlib::target::pin_out sclr = hwlib::target::pin_out(2, 28); // D3
	hwlib::target::pin_out g = hwlib::target::pin_out(1, 25); // D2
	
	hc595 chip = hc595(si, sck, rck, sclr, g);
	
	uint_fast8_t arrayOfData[8] = {1, 2, 4, 8, 16, 32, 64, 128};
		
	while(true){
		for(uint_fast8_t i : arrayOfData){
			chip.writeData(i);
			hwlib::wait_ms(1000);
		}
	}
}
