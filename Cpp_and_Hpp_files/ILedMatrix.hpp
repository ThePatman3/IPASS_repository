#ifndef ILEDMATRIX_HPP
#define ILEDMATRIX_HPP

/// @file

namespace lmtlib{

/// \brief
/// ILedMatrix interface/abstract class
/// \details
/// This interface is used for ledMatrixes.
class ILedMatrix{
public:
	/// \brief
	/// Constructor
	/// \details
	/// This constructor does nothing.
	ILedMatrix(){}
	
	/// \brief
	/// setLedValue function
	/// \details
	/// This function is used to turn on a led on the matrix. color is an integer value where; 0 = red, 1 = green, 2 = blue
	virtual void setLedValue(int color, int x, int y, bool value) = 0;
	
	/// \brief
	/// clear function
	/// \details
	/// This function is used to turn off all leds on the matrix
	virtual void clear() = 0;
	
	/// \brief
	/// lightMatrix function
	/// \details
	/// This function is used to turn on the matrix for one iteration. the int waitTime_ns is the amount of time that is waited between the activation between each row.
	virtual void lightMatrix(int waitTime_ns) = 0;
	
	/// \brief
	/// getSizeX function
	/// \details
	/// This function returns the size of the matrix on the x-axis
	virtual int getSizeX() = 0;
	
	/// \brief
	/// getSizeY function
	/// \details
	/// This function returns the size of the matrix on the y-axis
	virtual int getSizeY() = 0;
};

} // lmtlib

#endif
