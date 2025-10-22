/*
 * MySnake.cpp
 *
 *  Created on: Oct 3, 2025
 *      Author: jcgauthier 2212198
 *      		abdul ershad abdul ali 2285559
 */

#include "MySnake.h"
using namespace ELE3312;


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

void MySnake::setup(ILI9341Display *display){


	snake_[1].x = 10 * (std::rand() % 24);
	snake_[1].y = 10 * (std::rand() % 32);
	snake_[1].id = tileType::SNAKE_HEAD;

	display_ = display;

}


int MySnake::getSpeedDelay(){
	return snakeSpeed_;
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
 * @brief Déplace le serpent d'une case.
 * @param eat Si vrai, le serpent grandit d’une unité.
 */
void MySnake::move(int eat){


	int old_x = snake_[head_].x;
	int old_y = snake_[head_].y;
	snake_[head_].id = tileType::SNAKE_BODY;

	snake_[head_].disp(*display_);

	head_ = ( head_ >= 99) ? 0 : (head_ + 1);

	switch(direction_){
		case direction::NORTH:
			setSnakeTile(head_, old_x, (old_y - 10), tileType::SNAKE_HEAD);
			break;

		case direction::WEST:
			setSnakeTile(head_, (old_x + 10), old_y, tileType::SNAKE_HEAD);
			break;

		case direction::SOUTH:
			setSnakeTile(head_, old_x, (old_y +10), tileType::SNAKE_HEAD);
			break;

		case direction::EAST:
			setSnakeTile(head_, (old_x - 10) , old_y , tileType::SNAKE_HEAD);
			break;

		default:
			break;
	}

	snake_[head_].disp(*display_);
	snake_[tail_].erase(*display_);

	if(!eat)
		tail_ = ( tail_ >= 99) ? 0 : (tail_ + 1);

	snake_[tail_].disp(*display_);
}

/**
 * @brief changer la position du snake sur le damier en fonction de la direction prise par le clavier
 * @param Si la direction est NORTH, la composante en y du snake diminuera de 10
 * 		  Si la direction est WEST, la composante en x du snake augmentera de 10
 * 		  Si la direction est SOUTH, la composante en y du snake augmentera de 10
 * 		  Si la direction est SOUTH, la composante en x du snake diminuera de 10
 */
void MySnake::turn(bool turnDirection){


	switch (direction_) {
	        case direction::NORTH:
	            direction_ = turnDirection ? direction::EAST : direction::WEST;
	            break;
	        case direction::SOUTH:
	        	direction_ = turnDirection ? direction::WEST : direction::EAST;
	        	break;
	        case direction::EAST:
	        	direction_ = turnDirection ? direction::SOUTH : direction::NORTH;
	        	break;
	        case direction::WEST:
	        	direction_ = turnDirection ? direction::NORTH : direction::SOUTH;
	        	break;
	        default:
	        	break;
	    }


}

/**
 * @brief determine la direction du serpent en fonction des entrées du clavier.
 * De plus, avec les touches 2 et 5 ont controles, l'accélération et la déccélation.
 *  * @param
 */
void MySnake::turnKeypad(KeyCode FirstKey) {

        switch (FirstKey) {
            case KeyCode::FOUR: // gauche
                turn(LEFT);
                break;
            case KeyCode::SIX: // droite
                turn(RIGHT);
                break;
            case KeyCode::TWO:
            	snakeSpeed_ = (snakeSpeed_ >= 100) ? snakeSpeed_ - 50 : 100;
            	break;
            case KeyCode::FIVE:
            	snakeSpeed_ = (snakeSpeed_ <= 300) ? snakeSpeed_ + 50 : 300;
            	break;
            default:
            	break;
        }
}

template<typename T>
int sign(T value) {
	return ((T(0) < value) - ( value < T(0)));
}

/**
 * @brief determine la direction du serpent avec l'accelerometre
 * @param x est la position en x du serpent et y est la position en y du serpent. La fonction modifie les variables X et Y en fonction de l'accelerometre
 */
void MySnake::turnGyro(float x, float y){



	float sensibility = 0.1f;

	if ( !(((x > 0 && x < sensibility) || ( x < 0 && x > - sensibility)) &&
	     ((y > 0 && y < sensibility) || ( y < 0 && y > - sensibility)))) {

	bool xInputIsGreater =  x*x > y*y;

		if(xInputIsGreater == true){
			if(sign(x) > 0){
				snakeSpeed_ = (snakeSpeed_ >= 100) ? snakeSpeed_ - 50 : 100;
			}else{
				snakeSpeed_ = (snakeSpeed_ <= 300) ? snakeSpeed_ + 50 : 300;
			}

		}else{

			if(sign(y) > 0){
				turn(LEFT);
			}else{
				turn(RIGHT);
			}
		}

	}
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
        fruits_[i].disp(*display_);
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











