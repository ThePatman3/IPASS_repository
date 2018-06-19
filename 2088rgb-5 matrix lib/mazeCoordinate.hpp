#ifndef MAZECOORDINATE_HPP
#define MAZECOORDINATE_HPP

#include "hwlib.hpp"
#include "2088rgb_5.hpp"
#include "led.hpp"

struct mazeCoordinate{
	int x;
	int y;
	bool isWall;
	
	mazeCoordinate(int _x, int _y, bool _isWall): x(_x), y(_y), isWall(_isWall) {}
	mazeCoordinate(): x(0), y(0), isWall(false) {}
	
	void updateCoordinate(int _x, int _y, bool _isWall);
	void updateIsWall(bool _isWall);
};

#endif