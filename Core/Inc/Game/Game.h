/*
 * Game.h
 *
 *  Created on: Oct 22, 2025
 *      Author: jcgauthier 2212198
 *      		abdul ershad abdul ali 2285559
 */

#ifndef SRC_GAME_GAME_H_
#define SRC_GAME_GAME_H_

#include "main.h"

#include "NucleoImp/Display/ILI9341Display.h"
#include "Interfaces/Keypad/Keypad.h"
#include "NucleoImp/Keypad/GPIOKeypad.h"
#include "NucleoImp/MotionInput/MPU6050MotionInput.h"
#include "NucleoImp/SerialCom/UART.h"
#include "NucleoImp/SerialCom/Ringbuffer.h"
#include "Game/Sections/Menu.h"
#include "Game/Sections/SnakeGame.h"
#include "Game/Sections/VictoryScreen.h"
#include "cpp_main.h"
#include "MySnake.h"
#include "Fruits.h"

#define BUFFER_SIZE 128

namespace ELE3312 {

enum class CommState{
	Unknown,
	Master,
	Slave

};


enum class GameState{
	InputMenu,
	GameModeMenu,
	SnakeGame,
	VictoryScreen

};

enum class ControlMode{
	INPUT,
	KEYPAD,
	GYRO
};


class Game {
public:
	Game();
	virtual ~Game();

	void setup(peripheral_handles *handles);
	void inputMenu();
	void gameModeMenu();

	void initMaster();
	void initSlave();

	void run();
	void gameOver();


private:

	peripheral_handles *handles_ = nullptr;

	static ILI9341Display display_;
	static MPU6050MotionInput motionInput_;
	static GPIOKeypad keypad_;
	static UART uart;

	// uart
	static Ringbuffer uartBuffer;
	static uint8_t buff[];

	static Menu menu_;
	static SnakeGame snakeGame_;
	static VictoryScreen victoryScreen_;


	CommState commState_{CommState::Unknown};
	ControlMode input_{ ControlMode::INPUT };
	GameState state_{ GameState::InputMenu};

	MySnake snake_;
	MySnake snakeOpp_;
	Fruits fruits_;


};

} /* namespace ELE3312 */

#endif /* SRC_GAME_GAME_H_ */
