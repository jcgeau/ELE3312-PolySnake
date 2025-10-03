/*
 * MySnake.cpp
 *
 *  Created on: Oct 3, 2025
 *      Author: jcgauthier
 */

#include "MySnake.h"

using namespace ELE3312;

MySnake::MySnake() {
	// TODO Auto-generated constructor stub
	std::srand(std::time(nullptr)); // seed with current time

	snake[0].x = 10 * (std::rand() % 24);
	snake[0].y = 10 * (std::rand() % 32);
	snake[0].id = tileType::SNAKE_HEAD;

}

MySnake::~MySnake() {
	// TODO Auto-generated destructor stub
}

void MySnake::display(){


	for(i = this->tail; i != this->head;){

		this->snake[i].disp(this->display);



	}

}

void MySnake::move(int eat){}
void MySnake::turn(int direction){}
