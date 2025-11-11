/*
 * Game.cpp
 *
 *  Created on: Oct 22, 2025
 *      Author: jcgauthier 2212198
 *      		abdul ershad abdul ali 2285559
 */

#include "Game/Game.h"
#include "NucleoImp/SerialCom/SerialFrame.h"

namespace ELE3312 {

ILI9341Display Game::display_;
MPU6050MotionInput Game::motionInput_;
GPIOKeypad Game::keypad_;
UART Game::uart;

Menu Game::menu_;
SnakeGame Game::snakeGame_;
VictoryScreen Game::victoryScreen_;

// uart
Ringbuffer Game::uartBuffer;
uint8_t Game::buff[BUFFER_SIZE]= {0};

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
	uart.setup(handles->huart, 5);

	menu_.setup(&display_, &keypad_, &uart);
	snakeGame_.setup(&display_, &motionInput_, &keypad_, &uart);

	snake_.setup(&display_, &uart);
	snakeOpp_.setup(&display_, &uart);
	fruits_.setup(&display_);
	uartBuffer.setup();


	display_.clearScreen();
	display_.drawString(0, 0, "2212198, 2285559", Color::WHITE);

}


/**
 * @brief affiche la partie du jeux de snake, ou on peut bouger le serpent, manger des fruits et perdre la partie
 * 
 */
void Game::run(){

	SerialFrame frame;
	volatile int delay = 0;

	while(1){
		// Check UART and dispatch messages
		if (uartBuffer.read(buff, BUFFER_SIZE) != 0) {
			frame.setMessage(buff, BUFFER_SIZE);

			switch (frame.getMessageType()){
				case MessageType::PlayerChoice:
					if (state_ == GameState::Menu) { // Only dispatch messages for the current state
						//menu_.handleRemote(frame.getPlayerChoiceMessage());
					}
					break;
				case MessageType::Direction :
					if (state_ == GameState::SnakeGame) { // Only dispatch messages for the current state
						//snakeGame_.handleRemote(frame.getLabyrinthMessage());
					}
					break;

				default:
					break;
			}
		}

		// Handle user input
		switch(state_){
			case GameState::Menu:
				keypad_.update();
				break;
			case GameState::SnakeGame:
				keypad_.update();
				motionInput_.update();
				break;
			case GameState::VictoryScreen:
				break;
			default:
				break;
		}


		HAL_Delay(1);
		delay++;

		if(delay > 100){

			switch(state_){
				case GameState::Menu:
					if(menu_.run() )
						commType_ = menu_.getType();
						state_ = GameState::SnakeGame;

					break;

				case GameState::SnakeGame:
					if (snakeGame_.run(commType_) )
						state_ = GameState::VictoryScreen;

					break;

				default:
					break;
			}

			delay = 0;
		}
	}




	/**

	while(1){


	// update du périphérique selon le mode de saisie
	switch(input_){
	case ControlMode::KEYPAD:
		keypad_.update();
		break;
	case ControlMode::GYRO:
		motionInput_.update();
		break;
	default:
		break;
	}

	if (delay >= snake_.getSpeedDelay() ) { // délai plus lent pour contrôler la vitesse du serpent

		fruits_.displayFruits();
	    snake_.move(fruits_.checkEatFruitV2(snake_.getHeadTile())); // utilisation de la méthode checkEatFruit en assembleur
	    fruits_.generateNewFruit();


	    // direction selon le mode
	    switch(input_){
	        case ControlMode::KEYPAD:
	        	if (keypad_.isAnnyKeyPressed())
	        		snake_.turnKeypad(keypad_.getFirstKeyPressed());
	            break;
	        case ControlMode::GYRO:
	            snake_.turnGyro(motionInput_.getX(), motionInput_.getY());
	            break;

	        default:
	        	break;
	    }

	    // displaySnake();
	    delay = 0;
	    HAL_Delay(50);

	    if(snake_.checkColisionV2()) // sortie de la méthode run() quand il y a une colision, utilisation de la methode checkColision implémenté en assembleur
	    	break;

	}
	**/
}


/**
 * @brief affiche l'écran de "game over"
 * 
 */
void Game::gameOver(){

	display_.clearScreen();
	display_.drawString(30, 0, "2212198 & 2285559", Color::WHITE);
	display_.drawString(120, 160, "GAME OVER", Color::RED);

}

/** @brief Method that takes data provided by the uart interrupt.
  * @details The received data is stored internally and complete messages are
  * dispatched to the corresponding game sections.
  * @param [in] data A byte of data received from the serial interface.
  */
void Game::handleUART(uint8_t data){
	uartBuffer.write(&data, 1);
}

/** @brief Method that takes data provided by the uart interrupt.
  * @details The received data is stored internally and complete messages are
  * dispatched to the corresponding game sections.
  * @param [in] data A byte array of data received from the serial interface.
  * @param [in] size The number of bytes in the buffer to be written.
  */
void Game::handleUART(uint8_t *data, uint16_t size){
	uartBuffer.write(data, size);

}

} /* namespace ELE3312 */
