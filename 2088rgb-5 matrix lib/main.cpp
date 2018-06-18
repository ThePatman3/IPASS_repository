#include "hwlib.hpp"
#include "HC595.hpp"
#include "2088rgb_5.hpp"

int main(){
	
	// kill the watchdog
	WDT->WDT_MR = WDT_MR_WDDIS;
	
	// anodeController setup
	hwlib::target::pin_out rck = hwlib::target::pin_out(3, 7); // D11 Common register clock
	
	hwlib::target::pin_out anode_si = hwlib::target::pin_out(1, 25); // D2
	hwlib::target::pin_out anode_sck = hwlib::target::pin_out(3, 8); // D12
	hwlib::target::pin_out anode_sclr = hwlib::target::pin_out(2, 28); // D3
	
	hc595 anodeController = hc595(anode_si, anode_sck, rck, anode_sclr);
	
	// blueController setup
	hwlib::target::pin_out blue_si = hwlib::target::pin_out(2, 24); // D6
	hwlib::target::pin_out blue_sck = hwlib::target::pin_out(1, 27); // D13
	hwlib::target::pin_out blue_sclr = hwlib::target::pin_out(2, 22); // D8
	
	hc595 blueController = hc595(blue_si, blue_sck, rck, blue_sclr);
	
	// dummy hc595 setup for unused led colors
	hc595 dummyController = hc595(hwlib::pin_out_dummy, hwlib::pin_out_dummy, hwlib::pin_out_dummy, hwlib::pin_out_dummy);
	
	rgb2088_5 matrix = rgb2088_5(anodeController, dummyController, dummyController, blueController);
	
	while(true){
		for(int x = 0; x<4; x++){
			for(int y = 0; y<4; y++){
				matrix.setLed(2, x, y);
				hwlib::wait_ms(1000);
			}
		}
	}
}
