#include "hwlib.hpp"

#include "joyStick.hpp"

int joyStick::getX(){
	int pinXValue = static_cast<int>(pinX.get());
	if(pinXValue < 1900){
		if(pinXValue < 1000){
			return -9;
		}
		return (pinXValue/100 - 19);
	}else if(pinXValue > 2100){
		if(pinXValue > 3000){
			return 9;
		}
		return pinXValue/100 - 21;
	}
	return 0;
}
int joyStick::getY(){
	int pinYValue = static_cast<int>(pinY.get());
	if(pinYValue < 1900){
		if(pinYValue < 1000){
			return -9;
		}
		return (pinYValue/100 - 19);
	}else if(pinYValue > 2100){
		if(pinYValue > 3000){
			return 9;
		}
		return pinYValue/100 - 21;
	}
	return 0;
}

int joyStick::getXRaw(){
	return static_cast<int>(pinX.get());
}

int joyStick::getYRaw(){
	return static_cast<int>(pinY.get());
}
