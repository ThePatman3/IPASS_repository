#include "hwlib.hpp"
#include "HC595.hpp"
#include "led.hpp"

#include "2088rgb_5.hpp"

void rgb2088_5::setLed(int color, int x, int y){
	ledControllers[color] -> writeData(~powTwo[x], false);
	anodeController.writeData(powTwo[y], false);
}

void rgb2088_5::setLed(led Led){
	ledControllers[Led.color] -> writeData(~powTwo[Led.positionX], false);
	anodeController.writeData(powTwo[Led.positionY], false);
}

void rgb2088_5::setRow(const led leds[], int numberOfLeds, int row, int color, bool checkLedIsOn){
	if(!(numberOfLeds > 0)){
		return;
	}
	if(row == -1){
		row = leds[0].positionY;
	}
	if(color == -1){
		color = leds[0].color;
	}
	int shiftData = 0;
	if(checkLedIsOn){
		int n = 0;
		for(int i=0; i<8; i++){
			if(leds[i].isOn){
				shiftData += powTwo[leds[i].positionX];
				n++;
				if(n>=numberOfLeds){
					break;
				}
			}
		}
	}else{
		for(int i = 0; i < numberOfLeds; i++){
			shiftData += powTwo[leds[i].positionX];
		}
	}
	anodeController.clear();
	ledControllers[color] -> writeData(~shiftData, false);
	anodeController.writeData(powTwo[row], false);
}

void rgb2088_5::setLedValue(int color, int x, int y, bool value){
	if(matrixLayout[color][y][x].isOn != value){
		matrixLayout[color][y][x].isOn = value;
		(value)? numberOfLedsOn[color][y] += 1 : numberOfLedsOn[color][y] -= 1;
	}
}

void rgb2088_5::lightMatrix(int_fast32_t waitTime_ns){
	int waitTime_us = waitTime_ns/1000;
	bool wait = false;
	for(int Y=0; Y<8; Y++){
		wait = false;
		for(int col = 0; col < 3; col++){
			setRow(matrixLayout[col][Y], numberOfLedsOn[col][Y], Y, col, true);
			if(numberOfLedsOn[col][Y] > 0){
				wait = true;
			}else{
				ledControllers[col] -> writeData(~0);
			}
		}
		if(wait){
			hwlib::wait_us(waitTime_us);
		}
	}
}

int rgb2088_5::getSizeX(){
	return 8;
}

int rgb2088_5::getSizeY(){
	return 8;
}
