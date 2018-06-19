#ifndef LIGHTNINGMAZE_HPP
#define LIGHTNINGMAZE_HPP

#include "hwlib.hpp"
#include "2088rgb_5.hpp"
#include "led.hpp"
#include "mazeCoordinate.hpp"

template<int sizeX, int sizeY>
class lightningMaze{
private:
	rgb2088_5 matrix;
	mazeCoordinate walls[sizeX][sizeY];
	
public:
	lightningMaze(rgb2088_5 _matrix): matrix(_matrix){
		for(int x = 0; x<sizeX; x++){
			for(int y = 0; y<sizeY; y++){
				walls[x][y].updateCoordinate(x,y,false);
			}
		}
	}
	
	void setWall(int x, int y, bool wall){
		walls[x][y].updateIsWall(wall);
	}
	
	void generateWalls(){
		for(int borderX=0; borderX<sizeX; borderX++){
			setWall(borderX, 0, true);
			setWall(borderX,sizeY-1,true);
		}
		for(int borderY = 1; borderY<sizeY-1; borderY++){
			setWall(0,borderY,true);
			setWall(sizeX-1,borderY,true);
		}
		int doorWay = 6;
		for(int x=2; x<sizeX; x+=2){
			for(int y=0; y<sizeY; y++){
				if(y==doorWay){
					continue;
				}
				setWall(x, y, true);
			}
			doorWay-=2;
		}
		
		setWall(7,2,false);
	}
	
	void start(){
		for(int x=0; x<sizeX; x++){
			for(int y=0; y<sizeY; y++){
				matrix.setLedValue(2, x, y, walls[x][y].isWall);
			}
		}
		int iterations = 0;
		while(iterations < 1000){
			matrix.lightMatrix(700000);
			iterations++;
		}
	}
};

#endif
