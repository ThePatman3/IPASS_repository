#ifndef JOYSTICK_HPP
#define JOYSTICK_HPP

#include "hwlib.hpp"

class joyStick{
private:
	hwlib::target::pin_adc pinX;
	hwlib::target::pin_adc pinY;
public:
	joyStick(hwlib::target::pin_adc _pinX, hwlib::target::pin_adc _pinY):
		pinX(_pinX), pinY(_pinY) {}
	int getX();
	int getY();
	int getXRaw();
	int getYRaw();
};

#endif