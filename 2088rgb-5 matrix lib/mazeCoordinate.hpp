#ifndef MAZECOORDINATE_HPP
#define MAZECOORDINATE_HPP

#include "hwlib.hpp"
#include "2088rgb_5.hpp"
#include "led.hpp"

/// @file

/// \brief
/// mazeCoordinate struct
/// \details
/// This struct is used to store information about a coordinate in a maze. It is primarily meant to be used in the lightningMaze class.
struct mazeCoordinate{
	/// \brief
	/// x coordinate
	/// \details
	/// Variable to store the x coordinate
	int x;
	
	/// \brief
	/// y coordinate
	/// \details
	/// Variable to store the y coordinate
	int y;
	
	/// \brief
	/// isWall variable
	/// \details
	/// Variable to store whether this coordinate is a wall in the maze or not.
	bool isWall;
	
	/// \brief
	/// isUndefined variable
	/// \details
	/// Variable to store whether this coordinate has already been defined as a passage or a wall, using any other function than the defaultConstructor.
	bool isUndefined;
	
	/// \brief
	/// constructor for a mazeCoordinate
	/// \details
	/// This constructor constructs a mazeCoordinate with the position (_x;_y). The parameter _isWall determines whether this coordinate is a wall or not.
	/// Because the parameter _isWall determines whether this coordinate is a passage or a wall, the isUndefined variable is set to false.
	mazeCoordinate(int _x, int _y, bool _isWall): x(_x), y(_y), isWall(_isWall), isUndefined(false) {}
	
	/// \brief
	/// default constructor
	/// \details
	/// This constructor constructs a coordinate with the position (0;0). Because it is still unknown whether this is a passage or a wall, the isUndefined variable is set to true.
	mazeCoordinate(): x(0), y(0), isWall(false), isUndefined(true) {}
	
	/// \brief
	/// updateCoordinate function
	/// \details
	/// This function is used to update this coordinates' position and its' isWall flag. Because the isWall flag is updated, the isUndefined variable is set to false.
	void updateCoordinate(int _x, int _y, bool _isWall);
	
	/// \brief
	/// updateIsWall function
	/// \details
	/// Function to update the isWall flag of this coordinate. Because the isWall flag is updated, the isUndefined variable is set to false. 
	void updateIsWall(bool _isWall);
};

#endif