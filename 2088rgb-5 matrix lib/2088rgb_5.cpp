#include "hwlib.hpp"
#include "HC595.hpp"
#include "led.hpp"

#include "2088rgb_5.hpp"
/*
class rgb2088_5{
private:
	hc595 & anodeController;
	hc595 *ledControllers[3];
	uint_fast8_t powTwo[8];
	led matrixLayout[3,8,8];
	int numberOfLedsOn[3,8];
	
public:
	rgb2088_5(hc595 &_anodeController, hc595 &redController, hc595 &greenController, hc595 &blueController):
		anodeController(_anodeController),
		ledControllers{&redController, &greenController, &blueController},
		powTwo{1, 2, 4, 8, 16, 32, 64, 128} {
			for(int color = 0; color < 3; color++){
				for(int y = 0; y < 8; y++){
					numberOfLedsOn[color,y] = 0;
					for(int x = 0; x<8; x++){
						matrixLayout[color,x,y].color = color;
						matrixLayout[color,x,y].positionX = x;
						matrixLayout[color,x,y].positionY = y;
					}
				}
			}
		}
	
	// to become private methods:
	void setLed(int color, int x, int y); // color: 0 = red; 1 = green; 2 = blue
	void setLed(led Led);
	void setRow(const led leds[], int numberOfLeds, int row = -1, int color = -1);
	
	// public methods:
	void setLedValue(int color, int x, int y, bool value);
	void lightMatrix();
};
*/

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
	for(int col = 0; col < 3; col++){
		for(int Y=0; Y<8; Y++){
			setRow(matrixLayout[col][Y], numberOfLedsOn[col][Y], Y, col, true);
			if(numberOfLedsOn[col][Y] > 0){
				hwlib::wait_us(waitTime_us);
			}else{
				ledControllers[col] -> writeData(~0);
			}
		}
	}
}
