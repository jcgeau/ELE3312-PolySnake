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
#include "MySnake.h"
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


MySnake snake;

/** @brief main function of the game.
  * @param [in] handles A pointer to a structure with peripheral handles from the HAL.
  */
 void cpp_main(peripheral_handles *handles) {

	 snake.setup(handles);
	 snake.menu();
	 snake.run();

	 while(1) {
		 //Your infinite CPP loop
	 }
}


