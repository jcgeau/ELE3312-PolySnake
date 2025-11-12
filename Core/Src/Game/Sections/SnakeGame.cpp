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

	localSnake.setup(disp, comm);
	remoteSnake.setup(disp, comm);

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

			if (keypad->isAnnyKeyPressed())
				localSnake.turnKeypad(keypad->getFirstKeyPressed());

			localSnake.turnGyro(gyro->getX(), gyro->getY());

			localSnake.move(false); //TODO ajouter la logique pour manger un fruit

			if(comm){
				SnakeMessage msg(localSnake.getDirection());
				comm->send(&msg);
			}


			// TODO ajouter une fonction pour regarder la collision des deux snake

			if( localSnake.checkColision() || remoteSnake.checkColision( localSnake.getHeadTile() ) ) // sortie de la méthode run() quand il y a une colision, utilisation de la methode checkColision implémenté en assembleur
				return true;
			//return true; // Run finished
			HAL_Delay(50);
			counter = 0;

		}
	return false; // Run incomplete
	//display_.clearScreen();
	//display_.drawString(30, 0, "2212198 & 2285559", Color::WHITE);


}



void SnakeGame::initialize(){

	disp->clearScreen();
	disp->drawString(30, 0, "2212198 & 2285559", Color::WHITE);

	switch(commType){

	case CommType::Master:
		localSnake.init1();
		remoteSnake.init2();
		// TODO initialiser les fruits

		break;
	case CommType::Slave:
		remoteSnake.init1();
		localSnake.init2();
		// TODO recevoir la metadata des fruits

		break;

	default:
		break;
	}



}


void SnakeGame::handleRemote(SnakeMessage msg){

	if(!msg.isValid()){
		return;
	}

	remoteSnake.setDirection(msg.getDirection());
	remoteSnake.move(false); // TODO ajouter la logique pour manger un fruit


}


} /* namespace ELE3312 */
