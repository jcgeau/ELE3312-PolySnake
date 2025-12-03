/*
 * Menu.cpp
 *
 *  Created on: Nov 1, 2025
 *      Author: jcgauthier
 *      		abdul ershad abdul ali 2285559
 */

#include "Game/Sections/Menu.h"

namespace ELE3312 {

/**@brief Default constructor for the Menu class.
  */
Menu::Menu() {}

/** @brief Setup routine for a Menu object.
  * @param graph Pointer to a Graphics object that is used to display the menu graphics.
  * @param keypad Pointer to a Keypad object that is used to select the player's game character.
  * @param comm Pointer to a Communication object that is used to exchange messages with another player.
  * @param rgb Pointer to an RGBLicht object, used to indicate the player's color.
  * @param players Pointer to a PlayerManager object that manages player meta data.
  */
void Menu::setup(Display *disp, Keypad *keypad, Communication *comm, RGBLight * rgbLed) {

	this->disp = disp;
	this->keypad = keypad;
	this->comm = comm;
	this->rgbLed = rgbLed;

}

/**
 * @brief returns the type of communication of the current microcontroler
 * 
 * @return CommType: Master, Slave or Unknown
 */
CommType Menu::getType(){
	return type;
}

/** @brief Method that contains the mechanics of the menu. It will update one frame.
  * @retval true Indicates that the player has chosen a game character.
  * @retval false Indicates that the player has not yet chosen a game character.
  */
bool Menu::run(){

	switch(state){
		case MenuState::Initialization:
			initialize();
			state = MenuState::Run;

		case MenuState::Run:

			if(type != CommType::Unknown){
					return true;
			}

			if (keypad->isAnnyKeyPressed()){
				switch(keypad->getFirstKeyPressed()){

					   case KeyCode::ONE:
						   type = CommType::Master;
						   if(comm){
							   int randSeed = std::time(nullptr);
							   std::srand(randSeed);
							   CommTypeMessage msg(CommType::Master, randSeed);
							   comm->send(&msg);
							}
						   return true;

					   case KeyCode::THREE:
						   type = CommType::Slave;
						   if(comm){
							   int randSeed = HAL_GetTick();
							   std::srand(randSeed);
							   CommTypeMessage msg(CommType::Slave, randSeed);
							   comm->send(&msg);
							}
						   return true;

					   default:
						   return false;
				}
			}

	}
	return false; // Run incomplete
}

/** @brief Initializes the menu.
  */
void Menu::initialize(){

	rgbLed->setColorRGB(255,255,50);
	disp->clearScreen();
	disp->drawString(30, 0, "2212198 & 2285559", Color::WHITE);
	disp->drawString(110, 170, "player 1: 1 \n Player 2: 3", Color::WHITE);
	rgbLed->turnOn();


}

/** @brief Handles incoming messages.
  * @param [in] msg CommTypeMessage containing the player choice and random seed.
  */
void Menu::handleRemote(CommTypeMessage msg){

	if(!msg.isValid()){
		return;
	}

	std::srand(msg.getRandSeed());

	switch(msg.getCommType()){

	case CommType::Master:
		type = CommType::Slave;
		break;
	case CommType::Slave:
		type = CommType::Master;
		break;


	default:
		return;

	}

}

} /* namespace ELE3312 */

/**
  * @}
  */
