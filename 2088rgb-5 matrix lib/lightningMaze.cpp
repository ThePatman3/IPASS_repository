#include "hwlib.hpp"
#include "2088rgb_5.hpp"
#include "led.hpp"

#include "lightningMaze.hpp"

void mazeCoordinate::updateCoordinate(int _x, int _y, bool _isWall){
	x = _x;
	y = _y;
	isWall = _isWall;
}

void mazeCoordinate::updateIsWall(bool _isWall){
	isWall = _isWall;
}
