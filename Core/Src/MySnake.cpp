/*
 * MySnake.cpp
 *
 *  Created on: Oct 3, 2025
 *      Author: jcgauthier 2212198
 *      		abdul ershad abdul ali 2285559
 */

#include "MySnake.h"

namespace ELE3312{

MySnake::MySnake() {}

MySnake::~MySnake() {}


/**
 * @brief assigne l'addresse de l'objet display au snake
 * 
 * @param display pointeur vers l'objet permettant l'affichage des composantes
 */
void MySnake::setup(Display *display){
	display_ = display;
}

/**
 * @brief initialise la position initiale du serpent de manière aléatoire sur l'écran
 * 
 */
void MySnake::init1(){
	snake_[1].x = 160;
	snake_[1].y = 180; // toujours initialiser le serpent dans la moitié basse de l'écran
	snake_[1].id = tileType::SNAKE_HEAD1;
	direction_ = Direction::NORTH;
	HEAD = tileType::SNAKE_HEAD1;
	BODY = tileType::SNAKE_BODY1;
	snake_[1].disp(display_);
}

/**
 * @brief initialise la position initiale du serpent de manière aléatoire sur l'écran
 *
 */
void MySnake::init2(){
	snake_[1].x = 160;
	snake_[1].y = 60; // toujours initialiser le serpent dans la moitié basse de l'écran
	snake_[1].id = tileType::SNAKE_HEAD2;
	direction_ = Direction::SOUTH;
	HEAD = tileType::SNAKE_HEAD2;
	BODY = tileType::SNAKE_BODY2;
	snake_[1].disp(display_);

}

/**
 * @brief retourne le délai de vitesse du serpent
 * 
 * @return int délai de vitesse du serpent ( # d'updates / snakeSpeed[ms] )
 */
int MySnake::getSpeedDelay(){
	return snakeSpeed_;
}

/**
 * @brief retourne la tuile de la tête du serpent
 * 
 * @return tile la tuile de la tête du serpent
 */
tile MySnake::getHeadTile(){
	return snake_[head_];
}

Direction MySnake::getDirection(){
	return direction_;
}

/**
 * @brief mettre des paramètres dans une tuile du serpent
 * 
 * @param index position dans le tableau de tuiles du serpent
 * @param x position en x sur l'écran [0, 320]
 * @param y position en y sur l'écran [0, 240]
 * @param id détermine la couleur de la tuile 
 */
void MySnake::setSnakeTile(int index, int x, int y, tileType id){

	snake_[index].x = x;
	snake_[index].y = y;
	snake_[index].id = id;

}

void MySnake::setDirection(Direction direction){
	direction_ = direction;
}


/**
 * @brief Déplace le serpent d'une case dans la Direction courante et affiche le serpent
 *		  en effacant (ou non si il mange) la tuile de queue et en affichant la nouvelle position de tête
 *
 * @param eat Si vrai, le serpent grandit d’une unité.
 */
bool MySnake::move(bool eat){


	int old_x = snake_[head_].x;
	int old_y = snake_[head_].y;
	snake_[head_].id = BODY;

	snake_[head_].disp(display_);

	head_ = ( head_ >= 99) ? 0 : (head_ + 1);

	switch(direction_){
		case Direction::NORTH:
			setSnakeTile(head_, old_x, (old_y - 10), HEAD);
			break;

		case Direction::WEST:
			setSnakeTile(head_, (old_x + 10), old_y, HEAD);
			break;

		case Direction::SOUTH:
			setSnakeTile(head_, old_x, (old_y +10), HEAD);
			break;

		case Direction::EAST:
			setSnakeTile(head_, (old_x - 10) , old_y , HEAD);
			break;

		default:
			break;
	}

	snake_[head_].disp(display_);
	snake_[tail_].erase(display_);

	if(!eat){
		tail_ = ( tail_ >= 99) ? 0 : (tail_ + 1);
		return false;
	}

	snake_[tail_].disp(display_);

	return true;
}

/**
 * @brief détermine la Direction courante après un changement de Direction a gauche ou a droite
 * 
 * @param turnDirection RIGHT = true, LEFT = false 
 */
void MySnake::turn(bool turnDirection){

	switch (direction_) {
	        case Direction::NORTH:
	            direction_ = turnDirection ? Direction::EAST : Direction::WEST;
	            break;
	        case Direction::SOUTH:
	        	direction_ = turnDirection ? Direction::WEST : Direction::EAST;
	        	break;
	        case Direction::EAST:
	        	direction_ = turnDirection ? Direction::SOUTH : Direction::NORTH;
	        	break;
	        case Direction::WEST:
	        	direction_ = turnDirection ? Direction::NORTH : Direction::SOUTH;
	        	break;
	        default:
	        	break;
	    }
}

 /**
  * @brief Determine le changement de Direction du serpent en fonction des entrées du clavier.
  * 	   De plus, avec les touches 2 et 5 on peut controler l'accélération et la déccélation du serpent
  * 
  * @param FirstKey la première touche qui est appuyé sur le clavier
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

/**
 * @brief fonction template pour déterminer le signe d'une valeur signé
 *
 */
template<typename T>
int sign(T value) {
	return ((T(0) < value) - ( value < T(0)));
}
 
 /**
  * @brief Determine le changement de Direction du serpent avec l'acceleromètre, on peut aussi accélérer le serpent ou le déccélérer.
  *        Les deux paramètres sont contrôlés avec l'inclinaison de l'acceleromètre
  * 
  * @param x inclinaison en x du gyroscope
  * @param y inclinaison en y du gyroscope
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
 * @brief détermine si le serpent entre en colision avec son cors ou avec un des bords de l'écran
 * 
 * @return true le serpent est en colision avec sa queue ou le bord
 * @return false le serpent n'est pas en colision
 */
bool MySnake::checkColision(){

	if(snake_[head_].x >= 320)
		return true;

	if(snake_[head_].y >= 240)
		return true;

	for(int i = tail_; i != head_;){
		if( (snake_[head_].x == snake_[i].x) && (snake_[head_].y == snake_[i].y) )
			return true;
		i = (i >= 99) ? 0 : (i + 1);

	}

	return false;
}

bool MySnake::checkColision(tile oppHead){

	if((oppHead.x == snake_[head_].x) && (oppHead.y == snake_[head_].y))
		return true;

	for(int i = tail_; i != head_;){
		if( (oppHead.x == snake_[i].x) && (oppHead.y == snake_[i].y) )
			return true;
		i = (i >= 99) ? 0 : (i + 1);

	}

	return false;
}

/**
 * @brief implémentation en assembleur de la fonction checkColision
 * 
 */
extern "C" bool checkColision_asm(MySnake *self);

/**
 * @brief Appel de la fonction checkColision_asm implémenté en assembleur
 * 
 * @return true le serpent est en colision avec sa queue ou le bord
 * @return false le serpent n'est pas en colision
 */
bool MySnake::checkColisionV2() {
    return checkColision_asm(this);
}

}











