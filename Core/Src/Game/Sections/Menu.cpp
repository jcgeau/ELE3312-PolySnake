/*
 * Menu.cpp
 *
 *  Created on: Nov 1, 2025
 *      Author: jcgauthier
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
void Menu::setup(Display *disp, Keypad *keypad, Communication *comm) {

	this->disp = disp;
	this->keypad = keypad;
	this->comm = comm;

}

CommType Menu::getType(){
	return type;
}

/** @brief Method that contains the mechanics of the menu. It will update one frame.
  * @retval true Indicates that the player has chosen a game character.
  * @retval false Indicates that the player has not yet chosen a game character.
  */
bool Menu::run(){

	if(type != CommType::Unknown){
		return true;
	}


	switch(state){
		case MenuState::Initialization:
			initialize();
			state = MenuState::Run;

		case MenuState::Run:
			if (keypad->isAnnyKeyPressed()){

				switch(keypad->getFirstKeyPressed()){

					   case KeyCode::ONE:
						   type = CommType::Master;
						   return true;

					   case KeyCode::THREE:
						   type = CommType::Slave;
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

	disp->clearScreen();
	disp->drawString(30, 0, "2212198 & 2285559", Color::WHITE);
	disp->drawString(110, 170, "Keypad: 1 \n Gyro: 3", Color::WHITE);


}

/** @brief Handles incoming messages.
  * @param [in] msg PlayerChoiceMessage containing the character choice of the other player.
  */
void Menu::handleRemote(CommTypeMessage msg){

	if(!msg.isValid()){
		return;
	}

	switch(msg.getCommType()){

	case CommType::Master:
		type = CommType::Slave;
		break;
	case CommType::Slave:
		type = CommType::Master;
		break;


	default:
		return

	}

}

} /* namespace ELE3312 */

/**
  * @}
  */
