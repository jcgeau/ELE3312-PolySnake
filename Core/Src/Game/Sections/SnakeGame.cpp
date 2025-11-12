/*
 * SnakeGame.cpp
 *
 *  Created on: Nov 1, 2025
 *      Author: jcgauthier
 */

#include "Game/Sections/SnakeGame.h"

namespace ELE3312 {

SnakeGame::SnakeGame() {}

SnakeGame::~SnakeGame() {}

void SnakeGame::setup(Display *disp, MotionInput *gyro, Keypad* keypad, Communication *comm){
	this->disp = disp;
	this->gyro = gyro;
	this->keypad = keypad;
	this->comm = comm;
	opponentEncountered = false;

	localSnake.setup(disp);
	remoteSnake.setup(disp);
	fruits.setup(disp, comm);

}

bool SnakeGame::run(CommType commType){

	switch(state){
		case SnakeGameState::Initialization:
			this->commType = commType;
			initialize();
			state = SnakeGameState::Run;

		case SnakeGameState::Run:

			if(counter < localSnake.getSpeedDelay()){
				counter++;
				return false;
			}

			fruits.displayFruits();

			if (keypad->isAnnyKeyPressed())
				localSnake.turnKeypad(keypad->getFirstKeyPressed());

			localSnake.turnGyro(gyro->getX(), gyro->getY());

			if(localSnake.move(fruits.checkEatFruit(localSnake.getHeadTile()))){
				fruits.generateNewFruit();
			}

			if(comm){
				SnakeMessage msg(localSnake.getDirection());
				comm->send(&msg);
			}

			if( localSnake.checkColision() || remoteSnake.checkColision( localSnake.getHeadTile() ) ){

				if(comm){
					VictoryMessage msg(Winner::Winner);
					comm->send(&msg);
				}
				return true;

			}
			//return true; // Run finished
			HAL_Delay(50);
			counter = 0;

		}
	return false; // Run incomplete

}



void SnakeGame::initialize(){

	disp->clearScreen();
	disp->drawString(30, 0, "2212198 & 2285559", Color::WHITE);

	switch(commType){

	case CommType::Master:
		localSnake.init1();
		remoteSnake.init2();
		fruits.generateFruits();
		fruits.displayFruits();

		break;
	case CommType::Slave:
		remoteSnake.init1();
		localSnake.init2();
		fruits.generateFruits();
		fruits.displayFruits();

		break;

	default:
		break;
	}



}

void SnakeGame::handleRemote(FruitMessage msg){

	if(!msg.isValid()){
		return;
	}

	fruits.setFruit(msg.getFruit(), msg.getIndex());

}

void SnakeGame::handleRemote(SnakeMessage msg){

	if(!msg.isValid()){
		return;
	}

	remoteSnake.setDirection(msg.getDirection());

	if(remoteSnake.move(fruits.checkEatFruit(remoteSnake.getHeadTile()))){
		fruits.generateNewFruit();
	}

}


} /* namespace ELE3312 */
