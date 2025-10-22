/*
 * Game.h
 *
 *  Created on: Oct 22, 2025
 *      Author: jcgauthier
 */

#ifndef SRC_GAME_GAME_H_
#define SRC_GAME_GAME_H_

#include "main.h"

#include "NucleoImp/Display/ILI9341Display.h"
#include "Interfaces/Keypad/Keypad.h"
#include "NucleoImp/Keypad/GPIOKeypad.h"
#include "NucleoImp/MotionInput/MPU6050MotionInput.h"
#include "cpp_main.h"
#include "MySnake.h"


namespace ELE3312 {



enum class controlMode{
	INPUT,
	KEYPAD,
	GYRO
};


class Game {
public:
	Game();
	virtual ~Game();

	void setup(peripheral_handles *handles);
	void menu();
	void run();


private:

	peripheral_handles *handles_ = nullptr;

	static ILI9341Display display_;
	static MPU6050MotionInput motionInput_;
	static GPIOKeypad keypad_;

	controlMode mode_{ controlMode::INPUT };

	MySnake snake_;


};

} /* namespace ELE3312 */

#endif /* SRC_GAME_GAME_H_ */
