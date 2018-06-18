#ifndef RGB5Matrix_HPP
#define RGB5Matrix_HPP

#include "hwlib.hpp"
#include "HC595.hpp"
#include "led.hpp"

class rgb2088_5{
private:
	hc595 & anodeController;
	hc595 *ledControllers[3];
	uint_fast8_t powTwo[8];
	led matrixLayout[3][8][8]; // NOTE! x and y are reversed here, so: matrixLayout[color][y][x]
	int numberOfLedsOn[3][8]; // numberOfLedsOn[color][y]
	
public:
	rgb2088_5(hc595 &_anodeController, hc595 &redController, hc595 &greenController, hc595 &blueController):
		anodeController(_anodeController),
		ledControllers{&redController, &greenController, &blueController},
		powTwo{1, 2, 4, 8, 16, 32, 64, 128} {
			for(int color = 0; color < 3; color++){
				for(int y = 0; y < 8; y++){
					numberOfLedsOn[color][y] = 0;
					for(int x = 0; x<8; x++){
						matrixLayout[color][y][x].color = color;
						matrixLayout[color][y][x].positionX = x;
						matrixLayout[color][y][x].positionY = y;
					}
				}
			}
		}
	
	// to become private methods:
	void setLed(int color, int x, int y); // color: 0 = red; 1 = green; 2 = blue
	void setLed(led Led);
	void setRow(const led leds[], int numberOfLeds, int row = -1, int color = -1, bool checkLedIsOn = false);
	
	// public methods:
	void setLedValue(int color, int x, int y, bool value);
	void lightMatrix(int waitTime_ns);
};

#endif
