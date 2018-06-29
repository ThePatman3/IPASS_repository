#ifndef MULTIMATRIX_HPP
#define MULTIMATRIX_HPP

#include "hwlib.hpp"
#include "HC595.hpp"
#include "led.hpp"
#include "ILedMatrix.hpp"

/// @file

namespace lmtlib{

/// \brief
/// multiMatrix class
/// \details
/// Class to represent multiple matrices of the same size. The template parameters amountX and amountY determine how many matrices this class will represent.
/// Upon construction, this class will only contain one matrix, the matrix in the bottom left, additional matrices will have to be added using the addMatrix() function.
/// This class inherits from ILedMatrix.
template<int amountX, int amountY>
class multiMatrix : public ILedMatrix{
private:
	ILedMatrix *matrices[amountX][amountY];
	bool matrixPresent[amountX][amountY];
	int singleMatrixSizeX;
	int singleMatrixSizeY;
	
public:
	/// \brief
	/// multiMatrix constructor
	/// \details
	/// This constructor constructs a multiMatrix from one matrix, which will have to be positioned at the bottom left.
	multiMatrix(ILedMatrix &firstMatrix){
		matrices[0][0] = &firstMatrix;
		for(int x=0; x<amountX; x++){
			for(int y=0; y<amountY; y++){
				if(x==0 && y==0){
					matrixPresent[x][y] = true;
					continue;
				}
				matrixPresent[x][y] = false;
			}
		}
		singleMatrixSizeX = matrices[0][0] -> getSizeX();
		singleMatrixSizeY = matrices[0][0] -> getSizeY();
	}
	
	/// \brief
	/// addMatrix function
	/// \details
	/// This function is used add additional matrices to the multiMatrix. This does not increase the total number of matrices this multiMatrix can have,
	/// which is defined at construction using the template parameters.
	void addMatrix(ILedMatrix &matrix, int x, int y){
		matrices[x][y] = &matrix;
		matrixPresent[x][y] = true;
	}
	
	/// \brief
	/// setLedValue function
	/// \details
	/// This function is used to turn on a led on the matrix. color is an integer value where; 0 = red, 1 = green, 2 = blue
	void setLedValue(int color, int x, int y, bool value){
		int matrixIndexX = x/(singleMatrixSizeX);
		int matrixIndexY = y/(singleMatrixSizeY);
		
		matrices[matrixIndexX][matrixIndexY] -> setLedValue(color, x%singleMatrixSizeX, y%singleMatrixSizeY, value);
	}
	
	/// \brief
	/// clear function
	/// \details
	/// This function is used to turn off all leds on the matrix
	void clear(){
		for(int x = 0; x<amountX; x++){
			for(int y=0; y<amountY; y++){
				if(matrixPresent[x][y]){
					matrices[x][y] -> clear();
				}
			}
		}
	}
	
	/// \brief
	/// lightMatrix function
	/// \details
	/// This function is used to turn on the matrix for one iteration. the int waitTime_ns is the amount of time that is waited between the activation between each row.
	void lightMatrix(int waitTime_ns){
		for(int x = 0; x<amountX; x++){
			for(int y=0; y<amountY; y++){
				if(matrixPresent[x][y]){
					matrices[x][y] -> lightMatrix(waitTime_ns);
				}
			}
		}
	}
	
	/// \brief
	/// getSizeX function
	/// \details
	/// This function returns the size of the matrix on the x-axis
	int getSizeX(){
		int finalSize = 0;
		for(int x = 0; x<amountX; x++){
			if(matrixPresent[x][0]){
				finalSize += singleMatrixSizeX;
			}
		}
		return finalSize;
	}
	
	/// \brief
	/// getSizeY function
	/// \details
	/// This function returns the size of the matrix on the y-axis
	int getSizeY(){
		int finalSize = 0;
		for(int y = 0; y<amountY; y++){
			if(matrixPresent[0][y]){
				finalSize += singleMatrixSizeY;
			}
		}
		return finalSize;
	}
};

} // lmtlib

#endif
