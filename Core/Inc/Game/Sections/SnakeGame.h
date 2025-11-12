/*
 * SnakeGame.h
 *
 *  Created on: Nov 1, 2025
 *      Author: jcgauthier
 */

#ifndef SRC_GAME_SECTIONS_SNAKEGAME_H_
#define SRC_GAME_SECTIONS_SNAKEGAME_H_

#include "Interfaces/MotionInput/MotionInput.h"
#include "Interfaces/Display/Display.h"
#include "Interfaces/Communication/Communication.h"
#include "Game/ComMessages/SnakeMessage.h"
#include "Game/ComMessages/VictoryMessage.h"
#include "Game/ComMessages/CommTypeMessage.h"
#include "MySnake.h"
#include "Fruits.h"
#include <vector>
#include <cstdlib>
#include <ctime>

namespace ELE3312 {


enum class SnakeGameState {
	Initialization, Run
};


class SnakeGame {
public:
	SnakeGame();
	virtual ~SnakeGame();
	void setup(Display *disp, MotionInput *gyro, Keypad* keypad, Communication *comm);

	bool run(CommType commType);
	void handleRemote(FruitMessage msg);
	void handleRemote(SnakeMessage msg);

private:
	Display *disp = nullptr;
	MotionInput *gyro = nullptr;
	Communication *comm = nullptr;
	Keypad *keypad = nullptr;

	CommType commType = CommType::Unknown;
	MySnake localSnake;
	MySnake remoteSnake;
	Fruits fruits;

	bool opponentEncountered; //!< Indicates that the opponent was encountered.
	SnakeGameState state = SnakeGameState::Initialization;

	int counter{0};

	void initialize();

};

} /* namespace ELE3312 */

#endif /* SRC_GAME_SECTIONS_SNAKEGAME_H_ */
