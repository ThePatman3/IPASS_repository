#include "hwlib.hpp"
#include "HC595.hpp"

#include "2088rgb_5.hpp"
/*
class rgb2088_5{
private:
	hc595 & anodeController;
	hc595 *ledControllers[3];
	uint_fast8_t powTwo[8];
	
public:
	rgb2088_5(hc595 &_anodeController, hc595 &redController, hc595 &greenController, hc595 &blueController):
		anodeController(_anodeController),
		ledControllers{&redController, &greenController, &blueController},
		powTwo{1, 2, 4, 8, 16, 32, 64, 128} {}
	
	void setLed(int color, int x, int y);
}
*/

void rgb2088_5::setLed(int color, int x, int y){
	anodeController.writeData(powTwo[y]);
	ledControllers[color] -> writeData(~powTwo[x]);
}
