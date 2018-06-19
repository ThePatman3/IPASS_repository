#include "hwlib.hpp"
#include "HC595.hpp"
#include "2088rgb_5.hpp"
#include "led.hpp"
#include "lightningMaze.hpp"
#include "mazeCoordinate.hpp"

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
	
	// greenController setup
	hwlib::target::pin_out green_si = hwlib::target::pin_out(0, 15); // D24
	hwlib::target::pin_out green_sck = hwlib::target::pin_out(3, 1); // D26
	hwlib::target::pin_out green_sclr = hwlib::target::pin_out(1, 26); // D22
	
	hc595 greenController = hc595(green_si, green_sck, rck, green_sclr);
	
	// dummy hc595 setup for unused led colors
	hc595 dummyController = hc595(hwlib::pin_out_dummy, hwlib::pin_out_dummy, hwlib::pin_out_dummy, hwlib::pin_out_dummy);
	
	rgb2088_5 matrix = rgb2088_5(anodeController, dummyController, greenController, blueController);
/*
	for(int y = 6; y<8; y++){
		for(int x=1; x<7; x++){
			matrix.setLedValue(2, x, y, true);
		}
	}
	
	for(int y = 0; y<6; y++){
		for(int x=3; x<5; x++){
			matrix.setLedValue(2, x, y, true);
		}
	}
	
	matrix.setLedValue(1, 6, 1, true);
	matrix.setLedValue(1, 3, 7, true);
	
	int N = 0;
	int_fast32_t time_ns = 700000;
	while(N < 5000){
		matrix.lightMatrix(time_ns);
		N++;
	}
	*/
	
	lightningMaze<8,8> myGame = lightningMaze<8,8>(matrix);
	myGame.generateWalls();
	myGame.start();
	
}
