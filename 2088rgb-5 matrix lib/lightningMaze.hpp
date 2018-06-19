#ifndef LIGHTNINGMAZE_HPP
#define LIGHTNINGMAZE_HPP

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

template<int sizeX, int sizeY>
class lightningMaze{
private:
	rgb2088_5 matrix;
	mazeCoordinate walls[sizeX][sizeY];
	
public:
	lightningMaze(rgb2088_5 _matrix, int size): matrix(_matrix){
		for(int x = 0; x<sizeX(); x++){
			for(int y = 0; y<sizeY(); y++){
				walls[x][y].updateCoordinate(x,y,false);
			}
		}
	}
	
	void setWall(int x, int y, bool wall){
		walls[x][y].updateIsWall(wall);
	}
	
	void generateWalls(){
		int doorWay = 7;
		for(int x=1; x<sizeX(); x++){
			for(int y=0; y<sizeY(); y++){
				if(y==doorWay){
					continue;
				}
				setWall(x, y, true);
			}
			doorWay--;
		}
	}
};

#endif