/*
 * Fruits.h
 *
 *  Created on: Oct 22, 2025
 *      Author: jcgauthier
 */

#ifndef SRC_FRUITS_H_
#define SRC_FRUITS_H_

#include "tile.h"
#include "Interfaces/Display/Display.h"
#include "Interfaces/Communication/Communication.h"
#include "Game/ComMessages/FruitMessage.h"
#include "cpp_main.h"

#include <cstdlib>
#include <ctime>

namespace ELE3312 {

class Fruits {
public:
	Fruits();
	virtual ~Fruits();

	void setup(Display *display, Communication* comm);

	void setFruit(tile fruit, int index);

	void generateFruits();
	void displayFruits();
	void generateNewFruit();
	bool checkEatFruit(tile headTile);
	bool checkEatFruitV2(tile headTile);
	void sendFruit(tile fruit, int index);
	void sendFruits();

private:

	Display *display_ = nullptr;
	Communication *comm_ = nullptr;

	tile fruits_[100]; // 10 fruits maximum
	int fruitCount_{10};


};

} /* namespace ELE3312 */

#endif /* SRC_FRUITS_H_ */
