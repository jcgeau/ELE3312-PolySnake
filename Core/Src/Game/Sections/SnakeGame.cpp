/*
 * SnakeGame.cpp
 *
 *  Created on: Nov 1, 2025
 *      Author: jcgauthier
*      			abdul ershad abdul ali 2285559
 */

#include "Game/Sections/SnakeGame.h"

namespace ELE3312 {

/**
 * @brief Construct a new Snake Game:: Snake Game object
 * 
 */
SnakeGame::SnakeGame() {}

/**
 * @brief Destroy the Snake Game:: Snake Game object
 * 
 */
SnakeGame::~SnakeGame() {}

/** @brief Setup routine for a SnakeGame object.
  * @param disp Pointer to a Graphics object that is used to display the SnakeGame graphics.
  * @param keypad Pointer to a Keypad object that is used to select the player's game character.
  * @param comm Pointer to a Communication object that is used to exchange messages with another player.
  * @param gyro Pointer to an MPU6050 object, used to control the player.
  */
void SnakeGame::setup(Display *disp, MotionInput *gyro, Keypad* keypad, Distance *distance, Communication *comm, RGBLight *rgbLed){
	this->disp = disp;
	this->gyro = gyro;
	this->keypad = keypad;
	this->comm = comm;
	this->distance = distance;
	this->rgbLed = rgbLed;
	opponentEncountered = false;

	localSnake.setup(disp);
	remoteSnake.setup(disp);
	fruits.setup(disp, comm);

}

/**
 * @brief Method that contains the mechanics of the SnakeGame. It will update one frame.
 * 
 * @param commType 
 * @return true indicates the local snake has hit something and lost the game
 * @return false indicates no collision for the local snake is found and the game continues
 */
bool SnakeGame::run(CommType commType){

	switch(state){
		case SnakeGameState::Initialization:
			this->commType = commType;
			initialize();
			state = SnakeGameState::Run;

		case SnakeGameState::Run:
			// (counter < turboDelay) && (isTurbo()) ) ||
			if(  counter < localSnake.getSpeedDelay()){
				if((counter < turboDelay) || (!isTurbo())){
				counter++;
				return false;
				}
			}

			fruits.displayFruits();

			if (keypad->isAnnyKeyPressed())
				localSnake.turnKeypad(keypad->getFirstKeyPressed());

			localSnake.turnGyro(gyro->getX(), gyro->getY());

			if(localSnake.move(fruits.checkEatFruit(localSnake.getHeadTile()))){
				fruits.generateNewFruit();
			}

			if(comm){
				SnakeMessage msg(localSnake.getDirection(), localSnake.getTurbo());
				comm->send(&msg);
			}

			if( localSnake.checkColision() || remoteSnake.checkColision( localSnake.getHeadTile() ) ){

				if(comm){
					VictoryMessage msg(Winner::Winner); // envoi d'un message quand la partie est perdu par le joueur local
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

/**
 * @brief Initializes the SnakeGame
 * 
 */
void SnakeGame::initialize(){

	rgbLed->setColorRGB(255, 50,255);
	disp->clearScreen();
	disp->drawString(30, 0, "2212198 & 2285559", Color::WHITE);
	distance->enableMeasurement();

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

/**
 * @brief handles incoming messages
 * 
 * @param msg SnakeMessage containing the direction of the remote snake
 */
void SnakeGame::handleRemote(SnakeMessage msg){

	if(!msg.isValid()){
		return;
	}

	remoteSnake.setDirection(msg.getDirection());
	remoteSnake.setTurbo(msg.getTurbo());

	if(remoteSnake.move(fruits.checkEatFruit(remoteSnake.getHeadTile()))){
		fruits.generateNewFruit();
	}

}

bool SnakeGame::isTurbo(){

	if(distance->getDistance() < 5.0){
		localSnake.setTurbo(true);
		return localSnake.getTurbo();
	}

	localSnake.setTurbo(false);
	return false;

}


} /* namespace ELE3312 */
