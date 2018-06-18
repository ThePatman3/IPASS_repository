#ifndef LED_HPP
#define LED_HPP

#include "hwlib.hpp"

class led{
public:
	int color;
	int positionX;
	int positionY;
	bool isOn;
	
	led():
		color(1), positionX(0), positionY(0), isOn(false)
		{}
	led(int _color, int _positionX, int _positionY, bool _isOn = false):
		color(_color), positionX(_positionX), positionY(_positionY), isOn(_isOn)
		{}
	
};

#endif
