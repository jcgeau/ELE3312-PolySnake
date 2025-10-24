/*
 * Fruits.h
 *
 *  Created on: Oct 22, 2025
 *      Author: jcgauthier
 */

#ifndef SRC_FRUITS_H_
#define SRC_FRUITS_H_

#include "tile.h"
#include "NucleoImp/Display/ILI9341Display.h"
#include "Interfaces/Keypad/Keypad.h"
#include "NucleoImp/Keypad/GPIOKeypad.h"
#include "NucleoImp/MotionInput/MPU6050MotionInput.h"
#include "cpp_main.h"

#include <cstdlib>
#include <ctime>

namespace ELE3312 {

class Fruits {
public:
	Fruits();
	virtual ~Fruits();

	void setup(ILI9341Display *display);

	void generateFruits();
	void displayFruits();
	void generateNewFruit();
	bool checkEatFruit(tile headTile);
	bool checkEatFruitV2(tile headTile);

private:

	ILI9341Display *display_ = nullptr;

	tile fruits_[100]; // 10 fruits maximum
	int fruitCount_{10};


};

} /* namespace ELE3312 */

#endif /* SRC_FRUITS_H_ */
