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

MySnake snake;

/** @brief main function of the game.
  * @param [in] handles A pointer to a structure with peripheral handles from the HAL.
  */
 void cpp_main(peripheral_handles *handles) {


	 snake.setup(handles);
	 snake.menu();
	 std::srand(HAL_GetTick()); // seed with current time
	 snake.generateFruits();
	 snake.run();

	 while(1) {
		 //Your infinite CPP loop
	 }
}


