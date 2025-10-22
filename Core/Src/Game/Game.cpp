/*
 * Game.cpp
 *
 *  Created on: Oct 22, 2025
 *      Author: jcgauthier
 */

#include "Game/Game.h"

namespace ELE3312 {

ILI9341Display Game::display_;
MPU6050MotionInput Game::motionInput_;
GPIOKeypad Game::keypad_;

Game::Game() {
	// TODO Auto-generated constructor stub

}

Game::~Game() {
	// TODO Auto-generated destructor stub
}

void Game::setup(peripheral_handles *handles){

	this->handles_ = handles;
	display_.setup(handles->hspi_tft);
	motionInput_.setup(handles->hi2c);
	keypad_.setup(handles->gpio_keypad);
	snake_.setup(&display_);

	display_.clearScreen();
	display_.drawString(0, 0, "2212198, 2285559", Color::WHITE);

}

void Game::menu(){

	display_.clearScreen();
	display_.drawString(0, 0, "2212198 & 2285559", Color::WHITE);
	display_.drawString(110, 170, "Keypad: 1 \n Gyro: 3", Color::WHITE);

	while(mode_ == controlMode::INPUT){
		keypad_.update();
		switch(keypad_.getFirstKeyPressed()){

			   case KeyCode::ONE:
				   mode_ = controlMode::KEYPAD;
				   break;

			   case KeyCode::THREE:
				   mode_ = controlMode::GYRO;
				   break;

			   default:
				   break;
		}
	}

}

void Game::run(){

	snake_.generateFruits();

	volatile int delay = 0;

	display_.clearScreen();
	display_.drawString(0, 0, "2212198 & 2285559", Color::WHITE);

	while(1){


	switch(mode_){
	case controlMode::KEYPAD:
		keypad_.update();
		break;
	case controlMode::GYRO:
		motionInput_.update();
		break;
	default:
		break;
	}

	HAL_Delay(1);
	delay++;

	if (delay >= snake_.getSpeedDelay() ) {

		snake_.displayFruits();
	    snake_.move(snake_.checkEatFruit());


	    // direction selon le mode
	    switch(mode_){
	        case controlMode::KEYPAD:
	        	if (keypad_.isAnnyKeyPressed())
	        		snake_.turnKeypad(keypad_.getFirstKeyPressed());
	            break;
	        case controlMode::GYRO:
	            snake_.turnGyro(motionInput_.getX(), motionInput_.getY());
	            break;

	        default:
	        	break;
	    }

	    // displaySnake();
	    delay = 0;

	    HAL_Delay(50);
	}

}
}



} /* namespace ELE3312 */
