#ifndef JOYSTICK_HPP
#define JOYSTICK_HPP

#include "hwlib.hpp"

/// @file

namespace jstlib{

/// \brief
/// joyStick class
/// \details
/// This class represents a analog xy-axis joystick without button.
/// This class has functions to get the angle of the x and y axis rated using a number between -10 and 10 and functions to return the analog data directly.
class joyStick{
private:
	hwlib::target::pin_adc & pinX;
	hwlib::target::pin_adc & pinY;
public:
	/// \brief
	/// joyStick constructor
	/// \details
	/// This constructor constructs a joyStick from two hwlib::pin_adc for the x and y axis of the joystick.
	joyStick(hwlib::target::pin_adc & _pinX, hwlib::target::pin_adc & _pinY):
		pinX(_pinX), pinY(_pinY) {}
	
	/// \brief
	/// getX function
	/// \details
	/// This function returns a value between -10 and 10 to represent the angle the joystick currently has on its x-axis,
	/// where -10 is all the way to the left, and 10 is all the way to the right.
	int getX();
	
	/// \brief
	/// getY function
	/// \details
	/// This function returns a value between -10 and 10 to represent the angle the joystick currently has on its y-axis,
	/// where -10 is all the way down, and 10 is all the way up.
	int getY();
	
	/// \brief
	/// getXRaw function
	/// \details
	/// This function returns a value between 0 and 4096 to represent the angle the joystick currently has on its x-axis
	int getXRaw();
	
	/// \brief
	/// getYRaw function
	/// \details
	/// This function returns a value between 0 and 4096 to represent the angle the joystick currently has on its y-axis.
	int getYRaw();
};

} // jstlib;

#endif