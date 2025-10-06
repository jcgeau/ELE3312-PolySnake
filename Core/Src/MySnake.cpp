/*
 * MySnake.cpp
 *
 *  Created on: Oct 3, 2025
 *      Author: jcgauthier 2212198
 */

#include "MySnake.h"

using namespace ELE3312;

ILI9341Display MySnake::display_;
MPU6050MotionInput MySnake::motionInput_;
GPIOKeypad MySnake::keypad_;


MySnake::MySnake() {
	// TODO Auto-generated constructor stub



	std::srand(std::time(nullptr)); // seed with current time

	snake_[1].x = 10 * (std::rand() % 24);
	snake_[1].y = 10 * (std::rand() % 32);
	snake_[1].id = tileType::SNAKE_HEAD;

}



MySnake::~MySnake() {
	// TODO Auto-generated destructor stub
}

void MySnake::setup(peripheral_handles *handles){
	this->handles_ = handles;
	display_.setup(handles->hspi_tft);
	motionInput_.setup(handles->hi2c);
	keypad_.setup(handles->gpio_keypad);

	display_.clearScreen();
	display_.drawString(0, 0, "2212198", Color::WHITE);

}



void MySnake::menu(){
	display_.clearScreen();
	display_.drawString(0, 0, "2212198", Color::WHITE);
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
		}
	}


}



void MySnake::run(){

	int delay = 0;

	while(1){

	// handle inputs
	keypad_.update();
	motionInput_.update();
	HAL_Delay(1);
	delay++;

	if (delay == snakeSpeed_) {
		display_.clearScreen();


		displaySnake();
		move(0);

		switch(mode_){
			case controlMode::KEYPAD:
				turn( turnKeypad() );
				break;

			case controlMode::GYRO:
				turn( turnGyro(motionInput_.getX(), motionInput_.getY()) );
				break;

		}

		display_.drawString(0, 0, "2212198", Color::WHITE);
		delay = 0;
	}


	}
}


void MySnake::setSnakeTile(int index, int x, int y, tileType id){

	snake_[index].x = x;
	snake_[index].y = y;
	snake_[index].id = id;

}


void MySnake::displaySnake(){

	snake_[head_].disp(display_);

	for(int i = tail_; i != head_;){

		snake_[i].disp(display_);

		i = (i >= 99) ? 0 : (i + 1); // if i >= 99, i = 0 else i = i++
	}

}


void MySnake::move(int eat){


	int old_x = snake_[head_].x;
	int old_y = snake_[head_].y;
	snake_[head_].id = tileType::SNAKE_BODY;

	head_ = ( head_ >= 99) ? 0 : (head_ + 1);

	setSnakeTile(head_, old_x, old_y, tileType::SNAKE_HEAD);

	if(eat){
		tail_ = tail_;
	}else if(tail_ >= 99){
		tail_ = 0;
	}else{
		tail_++;
	}

}


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

	}

}


direction MySnake::turnKeypad(){

	if(keypad_.isAnnyKeyPressed()){

		switch(keypad_.getFirstKeyPressed()){

			   case KeyCode::TWO:
				   return direction::NORTH;

			   case KeyCode::SIX:
				   return direction::WEST;

			   case KeyCode::FIVE:
				   return direction::SOUTH;

			   case KeyCode::FOUR:
				   return direction::EAST;

			   default :
				   return direction_;
		}
	}

	return direction_;
}


template<typename T>
int sign(T value) {
	return ((T(0) < value) - ( value < T(0)));
}


direction MySnake::turnGyro(float x, float y){

	direction d;

	float sensibility = 0.1f;
	if ( ((x > 0 && x < sensibility) || ( x < 0 && x > - sensibility)) &&
	     ((y > 0 && y < sensibility) || ( y < 0 && y > - sensibility))) {
		return direction_;
	}

	bool xInputIsGreater =  x*x > y*y;

	if(xInputIsGreater == true){
		d = (sign(x) > 0) ? direction::NORTH : direction::SOUTH;
	}else{
		d = (sign(y) > 0) ? direction::EAST : direction::WEST;
	}


	return d;

}















