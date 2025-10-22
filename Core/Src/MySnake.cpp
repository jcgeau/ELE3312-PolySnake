/*
 * MySnake.cpp
 *
 *  Created on: Oct 3, 2025
 *      Author: jcgauthier 2212198
 *      		abdul ershad abdul ali 2285559
 */

#include "MySnake.h"
using namespace ELE3312;

ILI9341Display MySnake::display_;
MPU6050MotionInput MySnake::motionInput_;
GPIOKeypad MySnake::keypad_;


/**
 * @brief constructeur de la classe MySnake et fixer au hasard la tete du snake
 * @param
 */

MySnake::MySnake() {
	// TODO Auto-generated constructor stub


}



MySnake::~MySnake() {
	// TODO Auto-generated destructor stub
}

/**
 * @brief initialisation du graphique du jeu, de l'accelerometre, du clavier. (niveau plus bas ex:GPIO, i2c, etc)
 * @param
 */

void MySnake::setup(peripheral_handles *handles){

	this->handles_ = handles;
	display_.setup(handles->hspi_tft);
	motionInput_.setup(handles->hi2c);
	keypad_.setup(handles->gpio_keypad);

	display_.clearScreen();
	display_.drawString(0, 0, "2212198, 2285559", Color::WHITE);

	SystemCoreClockUpdate();
	printf("SystemCoreClock = %lu Hz\n", SystemCoreClock);
}


/**
 * @brief interface graphique du menu et la proposition de choix en le mode gyro ou clavier.
 * @param
 */
void MySnake::menu(){
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
 * @brief permet le déroulement du jeu. Met à jour le clavier ou l'accelerometre à chaque 1ms.
 * 		  permet aussi l'évolution des états des objets et du graphique du jeu.
 * @param
 */
void MySnake::run(){

	snake_[1].x = 10 * (std::rand() % 24);
	snake_[1].y = 10 * (std::rand() % 32);
	snake_[1].id = tileType::SNAKE_HEAD;

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

	HAL_Delay(10);
	delay++;

	if (delay == snakeSpeed_) {


	    // Vérifie si le serpent mange un fruit
	    bool eat = checkEatFruit();
	    move(eat);
	    displayFruits(); // afficher les fruits

	    // direction selon le mode
	    switch(mode_){
	        case controlMode::KEYPAD:
	            turn(turnKeypad());
	            break;
	        case controlMode::GYRO:
	            turn(turnGyro(motionInput_.getX(), motionInput_.getY()));
	            break;

	        default:
	        	break;
	    }

	    // displaySnake();
	    delay = 0;
	}

}
}

/**
 * @brief ecrit les position du snake en x et en y du snake et son identifiant
 * @param eat Si vrai, le serpent grandit d’une unité.
 */
void MySnake::setSnakeTile(int index, int x, int y, tileType id){

	snake_[index].x = x;
	snake_[index].y = y;
	snake_[index].id = id;

}

/**
 * @brief affiche le snake sur le damier
 * @param
 */
void MySnake::displaySnake(){

	snake_[head_].disp(display_);

	for(int i = tail_; i != head_;){

		snake_[i].disp(display_);

		i = (i >= 99) ? 0 : (i + 1); // if i >= 99, i = 0 else i++
	}

}

/**
 * @brief Déplace le serpent d'une case.
 * @param eat Si vrai, le serpent grandit d’une unité.
 */
void MySnake::move(int eat){


	int old_x = snake_[head_].x;
	int old_y = snake_[head_].y;
	snake_[head_].id = tileType::SNAKE_BODY;

	snake_[head_].disp(display_);

	head_ = ( head_ >= 99) ? 0 : (head_ + 1);

	setSnakeTile(head_, old_x, old_y, tileType::SNAKE_HEAD);

	snake_[tail_].erase(display_);

	if(!eat)
		tail_ = ( tail_ >= 99) ? 0 : (tail_ + 1);

	snake_[tail_].disp(display_);
}

/**
 * @brief changer la position du snake sur le damier en fonction de la direction prise par le clavier
 * @param Si la direction est NORTH, la composante en y du snake diminuera de 10
 * 		  Si la direction est WEST, la composante en x du snake augmentera de 10
 * 		  Si la direction est SOUTH, la composante en y du snake augmentera de 10
 * 		  Si la direction est SOUTH, la composante en x du snake diminuera de 10
 */
void MySnake::turn(direction direction){

	direction_ = direction;

	switch(direction){
		case direction::NORTH:
			setSnakeTile(head_, snake_[head_].x, (snake_[head_].y - 10), tileType::SNAKE_HEAD);
			break;

		case direction::WEST:
			setSnakeTile(head_, (snake_[head_].x + 10), snake_[head_].y, tileType::SNAKE_HEAD);
			break;

		case direction::SOUTH:
			setSnakeTile(head_, snake_[head_].x, (snake_[head_].y +10), tileType::SNAKE_HEAD);
			break;

		case direction::EAST:
			setSnakeTile(head_, (snake_[head_].x - 10) , snake_[head_].y , tileType::SNAKE_HEAD);
			break;

		default:
			break;

	}

	snake_[head_].disp(display_);
}

/**
 * @brief permet la rotation relative du serpent
 * @param Si turnLeft est vrai, c'est que l'on souhaite tourner a gauche selon sa direction initiale.
 * 		  Si turnLeft est faux, le snake souhaite tourner a droite selon sa direction initiale.
 */
direction MySnake::turnRelative(bool turnLeft) {

    switch (direction_) {
        case direction::NORTH:
            return turnLeft ? direction::EAST : direction::WEST;
        case direction::SOUTH:
            return turnLeft ? direction::WEST : direction::EAST;
        case direction::EAST:
            return turnLeft ? direction::SOUTH : direction::NORTH;
        case direction::WEST:
            return turnLeft ? direction::NORTH : direction::SOUTH;
        default:
        	return direction_;
    }
    return direction_;

}

/**
 * @brief determine la direction du serpent en fonction des entrées du clavier.
 * De plus, avec les touches 2 et 5 ont controles, l'accélération et la déccélation.
 *  * @param
 */
direction MySnake::turnKeypad() {
    if (keypad_.isAnnyKeyPressed()) {
        switch (keypad_.getFirstKeyPressed()) {
            case KeyCode::FOUR: // gauche
                return turnRelative(true);
            case KeyCode::SIX: // droite
                return turnRelative(false);
            case KeyCode::TWO:
            	snakeSpeed_ = (snakeSpeed_ >= 10) ? snakeSpeed_ - 5 : 10;
            	return direction_;
            	break;
            case KeyCode::FIVE:
            	snakeSpeed_ = (snakeSpeed_ <= 30) ? snakeSpeed_ + 5 : 30;
            	return direction_;
            	break;
            default:
                return direction_;
        }
    }
    return direction_;
}

template<typename T>
int sign(T value) {
	return ((T(0) < value) - ( value < T(0)));
}

/**
 * @brief determine la direction du serpent avec l'accelerometre
 * @param x est la position en x du serpent et y est la position en y du serpent. La fonction modifie les variables X et Y en fonction de l'accelerometre
 */
direction MySnake::turnGyro(float x, float y){



	float sensibility = 0.1f;
	if ( ((x > 0 && x < sensibility) || ( x < 0 && x > - sensibility)) &&
	     ((y > 0 && y < sensibility) || ( y < 0 && y > - sensibility))) {
		return direction_;
	}

	bool xInputIsGreater =  x*x > y*y;

	if(xInputIsGreater == true){
		if(sign(x) > 0){
			snakeSpeed_ = (snakeSpeed_ >= 100) ? snakeSpeed_ - 50 : 100;
			return direction_;
		}else{
			snakeSpeed_ = (snakeSpeed_ <= 300) ? snakeSpeed_ + 50 : 300;
			return direction_;
		}

	}else{
		if(sign(y) > 0){
			return turnRelative(true);
		}else{
			return turnRelative(false);
		}
	}

	return direction_;

}


/**
 * @brief genere la position des fruits aleatoirement et fixe le type de fruit
 *  * @param
 */
void MySnake::generateFruits() { //2285559
    for (int i = 0; i < fruitCount_; i++) {
          fruits_[i].x = (std::rand() % 24) * 10;
          fruits_[i].y = (std::rand() % 32) * 10;
          fruits_[i].id = tileType(3);

    }
}


/**
 * @brief affiche les fruits sur l'ecran
 * @param
 */
void MySnake::displayFruits() { //2285559
    for (int i = 0; i < fruitCount_; i++) {
        fruits_[i].disp(display_);
    }
}


/**
 * @brief Verifie si le serpent a mange un fruit.
 * @param Si la tete du serpent se trouve au meme endroit que les fruits, la fonction retourne true.
 */
bool MySnake::checkEatFruit() { //2285559
    for (int i = 0; i < fruitCount_; i++) {
        if (snake_[head_].x == fruits_[i].x && snake_[head_].y == fruits_[i].y) {
            // Le fruit est mangé → on le replace ailleurs
            fruits_[i].x = (std::rand() % 24) * 10;
            fruits_[i].y = (std::rand() % 32) * 10;
            return true;
        }
    }
    return false;
}











