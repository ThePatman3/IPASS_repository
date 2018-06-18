#ifndef MATRIXLAYOUT_HPP
#define MATRIXLAYOUT_HPP

#include "hwlib.hpp"
#include "led.hpp"

class matrix_layout{
private:
	led matrix[8,8];
	int numberOfLedsOn[8];
public:
	matrix_layout(int color){
		for(int y = 0; y < 8; y++){
			for(int x = 0; x<8; x++){
				matrix[x,y].color = color;
				matrix[x,y].positionX = x;
				matrix[x,y].positionY = y;
			}
		}
	}
	void setLedValue(int x, int y, bool value){
		if(matrix[x, y].isOn != value){
			matrix[x, y].isOn = value;
			numberOfLedsOn[y] = (value)? numberOfLedsOn[y] + 1 : numberOfLedsOn[y] - 1;
		}
	}
	
	int getNumberOfLedsOn(int y){
		return numberOfLedsOn[y];
	}
};

#endif
