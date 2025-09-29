/**
  * @file cpp_main.cpp
  * @date June 2025
  * @brief 
  * @authors: jean-christophe gauthier & ershad abdul ali
  * @defgroup ELE3312
  * @{
  */



/*
 *   in its current state, the random generation is deterministic every time the firmware is run but adding users inputs and a menu will solve the problem
 *
 *
 */


#include <memory>
#include <cstdio>
#include <string>

#include "main.h"
#include "tile.h"
#include <cpp_main.h>
#include <NucleoImp/Display/ILI9341Display.h>
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace ELE3312;


// generating random fruits and displaying them on the screen
void generate_fruits(ILI9341Display& display, tile fruits[]){

std::srand(std::time(nullptr)); // seed with current time
int randomNumber = std::rand() % 100 + 1; // range [1, 100]

int x{0};
int y{0};
int color{0};

for(uint16_t i = 0; i < randomNumber; i++){

	x = std::rand() % 24; // range [0,23]
	y = std::rand() % 32; // range [0,31]

	color = std::rand() % 2;

	fruits[i].x = x*10;
	fruits[i].y = y*10;

	if(color == 0)
		fruits[i].id = tileType::FRUIT_1;
	else
		fruits[i].id = tileType::FRUIT_2;

	fruits[i].disp(display);

}
}

void generate_snake(ILI9341Display& display, tile snake[]){

	std::srand(std::time(nullptr)); // seed with current time
	int randomNumber = std::rand() % 100 + 1; // range [1, 100]

	int x{0};
	int y{0};
	int direction{0}; //  represents the cardinal directions: north, east, west, south

	snake[0].id = tileType::SNAKE_HEAD; // display the first tile as the snake head

	x = std::rand() % 24; // range [0, 23]
	y = std::rand() % 32; // range [0, 31]

	snake[0].x = x*10; // normalizing coordinates to fit in 24x32 tile grid
	snake[0].y = y*10;

	snake[0].disp(display); // display the snake head

	for(uint16_t i = 1; i < randomNumber; i++){

		direction = std::rand() % 2; // range [0, 2]

		snake[i] = snake[i-1];
		snake[i].id = tileType::SNAKE_BODY;

		switch(direction){ // adding the direction to the next snake body part
		case 0: snake[i].x = snake[i].x + 10; break;
		case 1: snake[i].y = snake[i].y + 10; break;
		case 2: snake[i].y = snake[i].y - 10; break;

		}

		snake[i].disp(display); // display the element in a table

	}


}


ILI9341Display display;

tile fruits[100]; // array of fruits of max size 100
tile snake[100]; // array of snake of max size 100


/** @brief main function of the game.
  * @param [in] handles A pointer to a structure with peripheral handles from the HAL.
  */
 void cpp_main(peripheral_handles *handles) {

	 display.setup(handles->hspi_tft);
	 display.clearScreen();
	 generate_fruits(display, fruits); // generate and display fruits
	 generate_snake(display, snake); // generate and display snake
	 while(1) {
		 //Your infinite CPP loop
	 }
}


