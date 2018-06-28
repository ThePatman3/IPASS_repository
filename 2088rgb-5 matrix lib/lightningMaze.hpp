#ifndef LIGHTNINGMAZE_HPP
#define LIGHTNINGMAZE_HPP

#include "hwlib.hpp"
#include "2088rgb_5.hpp"
#include "led.hpp"
#include "mazeCoordinate.hpp"
#include "joyStick.hpp"
#include "ILedMatrix.hpp"

/// @file

namespace lightMaze{

/// \brief
/// lightningMaze Game
/// \details
/// lightningMaze is a game that uses a rgb2088_5 led matrix as display and
/// a joyStick for player input. The template parameters sizeX and sizeY determine the size of the maze.
/// After constructing a lightningMaze class the function generateWalls() has to be called.
/// When the function start() is called the lightingMaze will start its main loop, this loop is broken when the player has won.
template<int sizeX, int sizeY>
class lightningMaze{
private:
	lmtlib::ILedMatrix & matrix;
	mazeCoordinate walls[sizeX][sizeY];
	jstlib::joyStick & playerInput;
	mazeCoordinate playerCoordinate;
	mazeCoordinate exitCoordinate;
	int originX;
	int originY;
	int exitOriginX;
	int exitOriginY;
	
	void setWall(int x, int y, bool wall){
		walls[x][y].updateIsWall(wall);
	}
	
	int kindOfRandomNumber(int max){
		int firstNumber = playerInput.getXRaw();
		int secondNumber = playerInput.getYRaw();
		firstNumber ^= secondNumber;
		return firstNumber % (max+1);
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
	
public:
	/// \brief
	/// lightingMaze constructor
	/// \details
	/// This constructor constructs a lightningMaze class from a rgb2088_5 matrix and a joystick. The template parameters sizeX and sizeY determine the size of the maze.
	lightningMaze(lmtlib::ILedMatrix & _matrix, jstlib::joyStick & _playerInput): matrix(_matrix), playerInput(_playerInput), playerCoordinate(1,1,false), originX(0), originY(0), exitOriginX(0), exitOriginY(0){
		for(int x = 0; x<sizeX; x++){
			for(int y = 0; y<sizeY; y++){
				//walls[x][y].x = x;
				//walls[x][y].y = y;
				//walls[x][y].isWall = false;
				walls[x][y].updateCoordinate(x,y,false);
			}
		}
		for(int indexX = 1; indexX <= sizeX-2; indexX++){
			for(int indexY = 1; indexY <= sizeX-2; indexY++){
				if(indexX == 1 && indexY == 1){
					continue;
				}
				walls[indexX][indexY].isUndefined = true;
			}
		}
	}
	
	/// \brief
	/// generateWalls function
	/// \details
	/// This function generates the maze that the lightingMaze will use. This function is meant to be only called once,
	/// and it is not recommended to call it more than once as this would take time. Although, calling it multiple times shouldn't do anything destructive.
	void generateWalls(){
		for(int borderX=0; borderX<sizeX; borderX++){
			setWall(borderX, 0, true);
			setWall(borderX,sizeY-1,true);
		}
		for(int borderY = 1; borderY<sizeY-1; borderY++){
			setWall(0,borderY,true);
			setWall(sizeX-1,borderY,true);
		}
		
		mazeCoordinate neighbours[4];
		int amountUndefined = (sizeX-2) * (sizeY-2) - 1;
		bool deadEnd = true;
		mazeCoordinate currentCoordinate = playerCoordinate;
		walls[currentCoordinate.x][currentCoordinate.y] = currentCoordinate;
		exitCoordinate.x = sizeX-2;
		exitCoordinate.y = sizeY-2;
		bool foundNewCoordinate = false;
		int iterationsCheck = 0;
		while(amountUndefined > 0){ // needs cleanup!
			iterationsCheck++;
			if(iterationsCheck > (sizeX-1) * (sizeY-1)){
				break;
			}
			foundNewCoordinate = false;
			deadEnd = true;
			if(currentCoordinate.y + 1 <= sizeY -1){
				neighbours[0] = walls[currentCoordinate.x][currentCoordinate.y+1]; // top neighbour
			}else{
				neighbours[0] = walls[playerCoordinate.x][playerCoordinate.y];
			}
			if(currentCoordinate.x + 1 <= sizeX -1){
				neighbours[1] = walls[currentCoordinate.x + 1][currentCoordinate.y]; // right neighbour
			}else{
				neighbours[1] = walls[playerCoordinate.x][playerCoordinate.y];
			}
			if(currentCoordinate.y - 1 > 0){
				neighbours[2] = walls[currentCoordinate.x][currentCoordinate.y-1]; // bottom neighbour
			}else{
				neighbours[2] = walls[playerCoordinate.x][playerCoordinate.y];
			}
			if(currentCoordinate.x - 1 > 0){
				neighbours[3] = walls[currentCoordinate.x-1][currentCoordinate.y]; // left neighbour
			}else{
				neighbours[3] = walls[playerCoordinate.x][playerCoordinate.y];
			}
			int neighbourIndex = kindOfRandomNumber(3);
			for(int i = 0; i<4; i++){
				if(!neighbours[neighbourIndex].isUndefined){
					neighbourIndex = (neighbourIndex + 1) % 4;
					continue;
				}
				if(neighbours[neighbourIndex].x == exitCoordinate.x && neighbours[neighbourIndex].y == exitCoordinate.y){
					setWall(neighbours[neighbourIndex].x, neighbours[neighbourIndex].y, false);
					amountUndefined--;
					//currentCoordinate = neighbours[neighbourIndex];
					//deadEnd = false;
					neighbourIndex = (neighbourIndex + 1) % 4;
					continue;
				}
				if(!deadEnd){
					setWall(neighbours[neighbourIndex].x, neighbours[neighbourIndex].y, true);
					amountUndefined--;
					neighbourIndex = (neighbourIndex + 1) % 4;
					continue;
				}else{
					setWall(neighbours[neighbourIndex].x, neighbours[neighbourIndex].y, false);
					amountUndefined--;
					currentCoordinate = neighbours[neighbourIndex];
					deadEnd = false;
					neighbourIndex = (neighbourIndex + 1) % 4;
					continue;
				}
			}
			
			if(deadEnd){
				for(int x=1; x<=sizeX-2; x++){
					for(int y=1; y<=sizeY-2; y++){
						if(walls[x][y].isWall){
							if(y+1 < sizeY-2){
								if(walls[x][y+1].isUndefined){
									currentCoordinate = walls[x][y];
									setWall(currentCoordinate.x, currentCoordinate.y, false);
									foundNewCoordinate = true;
									break;
								}
							}else if(x+1 < sizeX-2){
								if(walls[x+1][y].isUndefined){
									currentCoordinate = walls[x][y];
									setWall(currentCoordinate.x, currentCoordinate.y, false);
									foundNewCoordinate = true;
									break;
								}
							}else if(y-1 > 0){
								if(walls[x][y-1].isUndefined){
									currentCoordinate = walls[x][y];
									setWall(currentCoordinate.x, currentCoordinate.y, false);
									foundNewCoordinate = true;
									break;
								}
							}else if(x-1 > 0){
								if(walls[x-1][y].isUndefined){
									currentCoordinate = walls[x][y];
									setWall(currentCoordinate.x, currentCoordinate.y, false);
									foundNewCoordinate = true;
									break;
								}
							}
						}
					}
					if(foundNewCoordinate){
						break;
					}
				}
				if(!foundNewCoordinate){
					return;
				}
			}
		}
		
		setWall(sizeX-1,2,false);
		
	}
	
	/// \brief
	/// start function
	/// \details
	/// This function starts the game and uses a loop which is only broken when the player wins.
	/// It is expected that the generateWalls() function is called before this one.
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

} //lightMaze

#endif
