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
#include "Game/ComMessages/CommTypeMessage.h"
#include "Game/Sections/Menu.h"
#include "Game/Sections/SnakeGame.h"
#include "Game/Sections/VictoryScreen.h"
#include "NucleoImp/SerialCom/SerialFrame.h"
#include "cpp_main.h"
#include "MySnake.h"
#include "Fruits.h"

#define BUFFER_SIZE 128

namespace ELE3312 {




enum class GameState{
	Menu,
	GameModeMenu,
	SnakeGame,
	VictoryScreen,
	Idle

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
	void gameModeMenu();

	void initMaster();
	void initSlave();

	void run();
	void gameOver();
	void winGame(VictoryMessage msg);

	void handleUART(uint8_t data);
	void handleUART(uint8_t *data, uint16_t size);


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


	CommType commType_{CommType::Unknown};
	GameState state_{ GameState::Menu};

	MySnake snake_;
	MySnake snakeOpp_;
	Fruits fruits_;


};

} /* namespace ELE3312 */

#endif /* SRC_GAME_GAME_H_ */
