/*
 * MySnake.h
 *
 *  Created on: Oct 3, 2025
 *      Author: jcgauthier 2212198
 */

#ifndef SRC_MYSNAKE_H_
#define SRC_MYSNAKE_H_

#include "main.h"

#include "tile.h"
#include "NucleoImp/Display/ILI9341Display.h"
#include "Interfaces/Keypad/Keypad.h"
#include "NucleoImp/Keypad/GPIOKeypad.h"
#include "NucleoImp/MotionInput/MPU6050MotionInput.h"
#include "Interfaces/Communication/Communication.h"
#include "cpp_main.h"

#include <cstdlib>
#include <ctime>


namespace ELE3312 {


enum class Direction {
	NORTH,
	WEST,
	SOUTH,
	EAST
};


class MySnake {
public:
	MySnake();
	virtual ~MySnake();

	void setup(Display *display, Communication *comm);
	void init1();
	void init2();

	int getSpeedDelay();
	tile getHeadTile();
	Direction getDirection();

	void setSnakeTile(int index, int x, int y, tileType id);

	void move(bool eat);
	void turn(bool turnDirection);

	void turnKeypad(KeyCode FirstKey);
	void turnGyro(float x, float y);

	void generateFruits();
	void displayFruits();
	bool checkEatFruit();

	bool checkColision();
	bool checkColisionV2();

	Direction turnRelative(bool turnLeft);

private:

	Display *display_ = nullptr;
	Communication *comm_ = nullptr;

	tile snake_[100];

	int head_{1};
	int tail_{0};

	int snakeSpeed_{200};
	Direction direction_{Direction::NORTH};

	tile fruits_[10]; // 10 fruits maximum
	int fruitCount_{10};

	static constexpr bool RIGHT{false};
	static constexpr bool LEFT{true};

};

} // End of namespace ELE3312

#endif /* SRC_MYSNAKE_H_ */
