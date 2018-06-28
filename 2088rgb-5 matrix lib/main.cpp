#include "hwlib.hpp"
#include "HC595.hpp"
#include "2088rgb_5.hpp"
#include "led.hpp"
#include "lightningMaze.hpp"
#include "mazeCoordinate.hpp"
#include "adc_pins.hpp"
#include "joyStick.hpp"
#include "ILedMatrix.hpp"
#include "multiMatrix.hpp"

int main(){
	
	// kill the watchdog
	WDT->WDT_MR = WDT_MR_WDDIS;
	
	// anodeController setup
	hwlib::target::pin_out rck = hwlib::target::pin_out(3, 7); // D11 Common register clock
	
	hwlib::target::pin_out anode_si = hwlib::target::pin_out(1, 25); // D2
	hwlib::target::pin_out anode_sck = hwlib::target::pin_out(3, 8); // D12
	hwlib::target::pin_out anode_sclr = hwlib::target::pin_out(2, 28); // D3
	
	lmtlib::hc595 anodeController = lmtlib::hc595(anode_si, anode_sck, rck, anode_sclr);
	
	// blueController setup
	hwlib::target::pin_out blue_si = hwlib::target::pin_out(2, 24); // D6
	hwlib::target::pin_out blue_sck = hwlib::target::pin_out(1, 27); // D13
	hwlib::target::pin_out blue_sclr = hwlib::target::pin_out(2, 22); // D8
	
	lmtlib::hc595 blueController = lmtlib::hc595(blue_si, blue_sck, rck, blue_sclr);
	
	// greenController setup
	hwlib::target::pin_out green_si = hwlib::target::pin_out(0, 15); // D24
	hwlib::target::pin_out green_sck = hwlib::target::pin_out(3, 1); // D26
	hwlib::target::pin_out green_sclr = hwlib::target::pin_out(1, 26); // D22
	
	lmtlib::hc595 greenController = lmtlib::hc595(green_si, green_sck, rck, green_sclr);
	
	// dummy hc595 setup for unused led colors
	lmtlib::hc595 dummyController = lmtlib::hc595(hwlib::pin_out_dummy, hwlib::pin_out_dummy, hwlib::pin_out_dummy, hwlib::pin_out_dummy);
	
	lmtlib::rgb2088_5 matrix = lmtlib::rgb2088_5(anodeController, dummyController, greenController, blueController);

	// joyStick setup
	hwlib::target::pin_adc adcPin0(hwlib::target::ad_pins::a0);
	hwlib::target::pin_adc adcPin1(hwlib::target::ad_pins::a1);
	jstlib::joyStick playerInput(adcPin1, adcPin0);
	
	lmtlib::multiMatrix<1,1> myMultiMatrix(matrix);
	
	// maze test
	//lightMaze::lightningMaze<16,16> myGame = lightMaze::lightningMaze<16,16>(matrix, playerInput);
	lightMaze::lightningMaze<16,16> myGame = lightMaze::lightningMaze<16,16>(myMultiMatrix, playerInput);
	myGame.generateWalls();
	myGame.start();
	
}
