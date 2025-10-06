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
#include "cpp_main.h"

#include <cstdlib>
#include <ctime>


namespace ELE3312 {

enum class direction {
	NORTH,
	WEST,
	SOUTH,
	EAST
};

enum class controlMode{
	INPUT,
	KEYPAD,
	GYRO
};


class MySnake {
public:
	MySnake();
	virtual ~MySnake();

	void setup(peripheral_handles *handles);
	void menu();
	void run();

	void setSnakeTile(int index, int x, int y, tileType id);

	void displaySnake();
	void move(int eat);

	void turn(direction d);
	direction turnKeypad();
	direction turnGyro(float x, float y);


private:

	peripheral_handles *handles_ = nullptr;

	static ILI9341Display display_;
	static MPU6050MotionInput motionInput_;
	static GPIOKeypad keypad_;

	tile snake_[100];
	int head_{1};
	int tail_{0};
	direction direction_{direction::NORTH};
	controlMode mode_{controlMode::INPUT};
	int snakeSpeed_{100};


};

} // End of namespace ELE3312

#endif /* SRC_MYSNAKE_H_ */
