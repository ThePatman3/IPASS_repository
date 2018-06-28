#ifndef RGB5Matrix_HPP
#define RGB5Matrix_HPP

#include "hwlib.hpp"
#include "HC595.hpp"
#include "led.hpp"
#include "ILedMatrix.hpp"

/// @file

/// \brief
/// rgb2088_5 class
/// \details
/// Class to represent a rgb2088_5 8x8 common anode rgb-led matrix. This class uses four hc595s' to control the leds on the matrix. This class inherits from ILedMatrix.
class rgb2088_5 : public ILedMatrix{
private:
	hc595 & anodeController;
	hc595 *ledControllers[3];
	uint_fast8_t powTwo[8];
	led matrixLayout[3][8][8]; // NOTE! x and y are reversed here, so: matrixLayout[color][y][x]
	int numberOfLedsOn[3][8]; // numberOfLedsOn[color][y]
	void setLed(int color, int x, int y); // color: 0 = red; 1 = green; 2 = blue
	void setLed(led Led);
	void setRow(const led leds[], int numberOfLeds, int row = -1, int color = -1, bool checkLedIsOn = false);
	
public:
	/// \brief
	/// rgb2088_5 constructor
	/// \details
	/// This constructor constructs a rgb2088_5 from four hc595. One to control the common anode, and one additional hc595 for every color.
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
	
	/// \brief
	/// setLedValue function
	/// \details
	/// This function is used to turn on a led on the matrix. color is an integer value where; 0 = red, 1 = green, 2 = blue
	void setLedValue(int color, int x, int y, bool value);
	
	/// \brief
	/// lightMatrix function
	/// \details
	/// This function is used to turn on the matrix for one iteration. the int waitTime_ns is the amount of time that is waited between the activation between each row, this value cannot be below 1000ns
	/// This function has been successfully tested using a 700000ns waitTime
	void lightMatrix(int waitTime_ns); // Successfully tested with a 700000ns waitTime
	
	/// \brief
	/// getSizeX function
	/// \details
	/// This function returns the size of the matrix on the x-axis
	int getSizeX();
	
	/// \brief
	/// getSizeY function
	/// \details
	/// This function returns the size of the matrix on the y-axis
	int getSizeY();
};

#endif
