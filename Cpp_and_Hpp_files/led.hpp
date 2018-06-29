#ifndef LED_HPP
#define LED_HPP

#include "hwlib.hpp"

/// @file

namespace lmtlib{

/// \brief
/// class to represent a led
/// \details
/// This class is used to represent an led on a rgb matrix. It has an integers to store its color, two integers to store its location on the x-axis and y-axis
/// and it has a boolean to store whether it is currently on or not.
class led{
public:
	/// \brief
	/// color integer variable
	/// \details
	/// Variable to store the color of this led.
	int color;
	
	/// \brief
	/// positionX integer variable
	/// \details
	/// Variable to store the position on the x-axis of this led.
	int positionX;
	
	/// \brief
	/// positionY integer variable
	/// \details
	/// Variable to store the position on the y-axis of this led.
	int positionY;
	
	/// \brief
	/// isOn boolean variable
	/// \details
	/// Variable to store whether this led is currently on.
	bool isOn;
	
	/// \brief
	/// default constructor
	/// \details
	/// This constructor constructs a green led on position (0;0) that is currently off.
	led():
		color(1), positionX(0), positionY(0), isOn(false)
		{}
	
	/// \brief
	/// led constructor
	/// \details
	/// This constructor constructs a led of the color _color, on the position (_positionX;_positionY). The parameter _isOn determines whether the led is currently on or not.
	led(int _color, int _positionX, int _positionY, bool _isOn = false):
		color(_color), positionX(_positionX), positionY(_positionY), isOn(_isOn)
		{}
	
};

} // lmtlib

#endif
