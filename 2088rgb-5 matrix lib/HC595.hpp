#ifndef HC595LIB_HPP
#define HC595LIB_HPP

#include "hwlib.hpp"

/// @file

namespace lmtlib{

/// \brief
/// class for an hc595 shift register
/// \details
/// Class to represent an hc595, which is an 8-bit serial input, parallel output shift register.
/// It has separate clocks for the shift register and the storage register and has a serial output for cascading.
/// This class has a writeData() function to write a byte to the hc595, a shiftData() function to shift all data one place to the Qh,
/// a clear() function to clear the data, a enableOutput() function to enable and disable the output
/// and lastly a function that returns the data currently stored on the hc595.
class hc595{
private:
	hwlib::pin_out & SI;
	hwlib::pin_out & SCK;
	hwlib::pin_out & RCK;
	hwlib::pin_out & SCLR;
	hwlib::pin_out & G;
	int waitTime_us;
	uint_fast8_t currentData;
	
public:
	/// \brief
	/// hc595 constructor
	/// \details
	/// This constructor constructs an hc595 from five hwlib::pin_out 's. 
	/// The _SI pin is used for the serial input, _SCK is used for the shift register's clock, _RCK is used for the storage register's clock,
	/// _SCLR is used to clear the shift register (without clearing the storage register) and the _G is used for the output enable pin;
	/// Although it is recommended that a _SCLR pin is provided, when this is not the case a dummy pin is used as default value.
	/// The _G pin also has a dummy as default value, when the dummy is used as the _G pin, the enableOutput function will not function properly.
	hc595(hwlib::pin_out & _SI, hwlib::pin_out & _SCK, hwlib::pin_out & _RCK, hwlib::pin_out & _SCLR = hwlib::pin_out_dummy, hwlib::pin_out & _G = hwlib::pin_out_dummy);
	
	/// \brief
	/// writeData function
	/// \details
	/// This function can be used to write data to the hc595. The parameter data is the byte that is to be send to the hc595,
	/// the boolean direction is used to determine in which order the data is to be send. When direction == true, the lsb will be placed at Qh and the msb will be placed at Qa.
	/// When direction == false, this is reversed. Direction has the default value false.
	void writeData(uint_fast8_t data, bool direction = false); // when direction == true, the lsb will be placed at Qh and the msb will be placed at Qa.
	
	/// \brief
	/// shiftData function
	/// \details
	/// This function shifts the data one place to the Qh. The parameter bit is used as new value for Qa
	void shiftData(bool bit = 0);
	
	/// \brief
	/// clear function
	/// \details
	/// This function clears both the storage and shift registers, replacing all data with 0.
	void clear();
	
	/// \brief
	/// enableOutput function
	/// \details
	/// This function controls whether the output should be enabled or not. When parameter enable == true, the output will be enabled, when false it will be disabled
	void enableOutput(bool enable);
	
	/// \brief
	/// get_currentData function
	/// \details
	/// This function returns the data that is currently being stored in the hc595.
	uint_fast8_t get_currentData();
};

} // lmtlib

#endif