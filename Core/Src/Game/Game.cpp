/*
 * Game.cpp
 *
 *  Created on: Oct 22, 2025
 *      Author: jcgauthier 2212198
 *      		abdul ershad abdul ali 2285559
 */

#include "Game/Game.h"

namespace ELE3312 {

ILI9341Display Game::display_;
MPU6050MotionInput Game::motionInput_;
GPIOKeypad Game::keypad_;

Game::Game() {}

Game::~Game() {}

/**
 * @brief initialise tout les périphériques pour nous permettres de les utiliser par la suite
 * 
 * @param handles 
 */
void Game::setup(peripheral_handles *handles){

	this->handles_ = handles;
	display_.setup(handles->hspi_tft);
	motionInput_.setup(handles->hi2c);
	keypad_.setup(handles->gpio_keypad);
	snake_.setup(&display_);
	fruits_.setup(&display_);


	display_.clearScreen();
	display_.drawString(0, 0, "2212198, 2285559", Color::WHITE);

}

/**
 * @brief affiche un menu ou on peut sélectionner le type de saisie pour contrôler le serpent
 * 
 * @param mode_ KEYPAD: on controle le serpent avec le clavier, GYRO: on contrôle le serpent avec l'accéléromètre
 * 
 */
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

/**
 * @brief affiche la partie du jeux de snake, ou on peut bouger le serpent, manger des fruits et perdre la partie
 * 
 */
void Game::run(){

	snake_.init();
	fruits_.generateFruits();

	volatile int delay = 0;

	display_.clearScreen();
	display_.drawString(0, 0, "2212198 & 2285559", Color::WHITE);

	while(1){

	// update du périphérique selon le mode de saisie
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

		fruits_.displayFruits();
	    snake_.move(fruits_.checkEatFruit(snake_.getHeadTile()));


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

	    if(snake_.checkColision()) // sortie de la méthode run() quand il y a une colision
	    	break;

	}

}
}

/**
 * @brief affiche l'écran de "game over"
 * 
 */
void Game::gameOver(){

	display_.clearScreen();
	display_.drawString(120, 160, "GAME OVER", Color::RED);

}

} /* namespace ELE3312 */
