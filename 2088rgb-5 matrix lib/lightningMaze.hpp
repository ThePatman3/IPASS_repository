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
	int originX;
	int originY;
	int exitOriginX;
	int exitOriginY;
	// bool winText[8][30];
public:
	lightningMaze(rgb2088_5 _matrix, joyStick _playerInput): matrix(_matrix), playerInput(_playerInput), playerCoordinate(1,1,false), originX(0), originY(0), exitOriginX(0), exitOriginY(0){
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
			doorWay = (doorWay-2 >= 1)? doorWay - 2 : doorWay;
		}
		
		setWall(sizeX-1,2,false);
		exitCoordinate.updateCoordinate(sizeX-1,2,false);
	}
	
	// heading: 0 = 0, 1 = Y+, 2 = X+, 3 = Y-, 4 = X-
	bool movePlayer(int x, int y){ // needs cleanup!
		int newCoordinateX = playerCoordinate.x + x;
		int newCoordinateY = playerCoordinate.y + y;
		if(walls[newCoordinateX][newCoordinateY].isWall){
			return false;
		}
		if(newCoordinateX >= originX + matrix.getSizeX()){
			matrix.setLedValue(1, playerCoordinate.x % matrix.getSizeX(), playerCoordinate.y % matrix.getSizeY(), false);
			originX += matrix.getSizeX();
			playerCoordinate.updateCoordinate(newCoordinateX, newCoordinateY, false);
			drawMaze();
			matrix.setLedValue(1, playerCoordinate.x % matrix.getSizeX(), playerCoordinate.y % matrix.getSizeY(), true);
		}else if(newCoordinateX < originX){
			matrix.setLedValue(1, playerCoordinate.x % matrix.getSizeX(), playerCoordinate.y % matrix.getSizeY(), false);
			originX -= matrix.getSizeX();
			playerCoordinate.updateCoordinate(newCoordinateX, newCoordinateY, false);
			drawMaze();
			matrix.setLedValue(1, playerCoordinate.x % matrix.getSizeX(), playerCoordinate.y % matrix.getSizeY(), true);
		}else if(newCoordinateY >= originY + matrix.getSizeY()){
			matrix.setLedValue(1, playerCoordinate.x % matrix.getSizeX(), playerCoordinate.y % matrix.getSizeY(), false);
			originY += matrix.getSizeY();
			playerCoordinate.updateCoordinate(newCoordinateX, newCoordinateY, false);
			drawMaze();
			matrix.setLedValue(1, playerCoordinate.x % matrix.getSizeX(), playerCoordinate.y % matrix.getSizeY(), true);
		}else if(newCoordinateY < originY){
			matrix.setLedValue(1, playerCoordinate.x % matrix.getSizeX(), playerCoordinate.y % matrix.getSizeY(), false);
			originY -= matrix.getSizeY();
			playerCoordinate.updateCoordinate(newCoordinateX, newCoordinateY, false);
			drawMaze();
			matrix.setLedValue(1, playerCoordinate.x % matrix.getSizeX(), playerCoordinate.y % matrix.getSizeY(), true);
		}else{
			matrix.setLedValue(1, playerCoordinate.x % matrix.getSizeX(), playerCoordinate.y % matrix.getSizeY(), false);
			playerCoordinate.updateCoordinate(newCoordinateX, newCoordinateY, false);
			matrix.setLedValue(1, playerCoordinate.x % matrix.getSizeX(), playerCoordinate.y % matrix.getSizeY(), true);
		}
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
	
	void drawMaze(){
		int maxX = (originX + 1 + matrix.getSizeX() > sizeX)? sizeX-1 : originX + matrix.getSizeX()-1; // the maximum valid x index
		int maxY = (originY + 1 + matrix.getSizeY() > sizeY)? sizeY-1 : originY + matrix.getSizeY()-1; // the maximum valid y index
		
		for(int x = originX; x<=originX + matrix.getSizeX()-1; x++){
			for(int y = originY; y<=originY + matrix.getSizeY()-1; y++){
				if(x>maxX || y>maxY){
					matrix.setLedValue(2, x-originX, y-originY, true);
				}else{
					matrix.setLedValue(2, x-originX, y-originY, walls[x][y].isWall);
				}
			}
		}
		
		if(exitOriginX == originX && exitOriginY == originY){
			matrix.setLedValue(1, exitCoordinate.x - exitOriginX, exitCoordinate.y - exitOriginY, true);
		}else{
			matrix.setLedValue(1, exitCoordinate.x - exitOriginX, exitCoordinate.y - exitOriginY, false);
		}
	}
	
	void start(){
		// initialize
		
		while(!(exitCoordinate.x - exitOriginX < matrix.getSizeX())){
			exitOriginX += matrix.getSizeX();
		}
		while(!(exitCoordinate.y - exitOriginY * matrix.getSizeY() < matrix.getSizeY())){
			exitOriginY += matrix.getSizeY();
		}
		
		drawMaze();
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
