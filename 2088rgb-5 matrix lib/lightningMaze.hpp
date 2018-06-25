#ifndef LIGHTNINGMAZE_HPP
#define LIGHTNINGMAZE_HPP

#include "hwlib.hpp"
#include "2088rgb_5.hpp"
#include "led.hpp"
#include "mazeCoordinate.hpp"
#include "joyStick.hpp"

template<int sizeX, int sizeY>
class lightningMaze{
private:
	rgb2088_5 matrix;
	mazeCoordinate walls[sizeX][sizeY];
	joyStick & playerInput;
	mazeCoordinate playerCoordinate;
	mazeCoordinate exitCoordinate;
	// bool winText[8][30];
public:
	lightningMaze(rgb2088_5 _matrix, joyStick _playerInput): matrix(_matrix), playerInput(_playerInput), playerCoordinate(1,1,false){
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
		exitCoordinate.updateCoordinate(7,2,false);
	}
	
	// heading: 0 = 0, 1 = Y+, 2 = X+, 3 = Y-, 4 = X-
	bool movePlayer(int x, int y){
		int newCoordinateX = playerCoordinate.x + x;
		int newCoordinateY = playerCoordinate.y + y;
		if(walls[newCoordinateX][newCoordinateY].isWall){
			return false;
		}
		matrix.setLedValue(1, playerCoordinate.x, playerCoordinate.y, false);
		playerCoordinate.updateCoordinate(newCoordinateX, newCoordinateY, false);
		matrix.setLedValue(1, playerCoordinate.x, playerCoordinate.y, true);
		if(playerCoordinate.x == exitCoordinate.x && playerCoordinate.y == exitCoordinate.y){
			return true;
		}
		return false;
	}
	
	bool update(){
		int inputX = playerInput.getX();
		int inputY = playerInput.getY();
		if(inputX > 5){ // player is moving X+
			return movePlayer(1, 0);
		}else if(inputX < -5){ // player is moving X-
			return movePlayer(-1, 0);
		}else if(inputY > 5){ // player is moving Y+
			return movePlayer(0, 1);
		}else if(inputY < -5){ // player is moving Y-
			return movePlayer(0, -1);
		}else{ // player is standing still
			return false;
		}
	}
	
	void start(){
		// initialize
		for(int x=0; x<sizeX; x++){
			for(int y=0; y<sizeY; y++){
				matrix.setLedValue(2, x, y, walls[x][y].isWall);
			}
		}
		matrix.setLedValue(1, exitCoordinate.x, exitCoordinate.y, true);
		matrix.setLedValue(1,playerCoordinate.x, playerCoordinate.y,true);
		// start the loop
		int iterations = 0;
		bool endgame = false;
		while(!endgame){
			matrix.lightMatrix(700000);
			if(iterations % 40 == 0){
				endgame = update();
				iterations = 1;
			}else{
				iterations++;
			}
		}
	}
};

#endif
