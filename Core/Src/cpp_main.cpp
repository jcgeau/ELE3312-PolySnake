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
#include "Game/Game.h"
#include <cpp_main.h>
#include <NucleoImp/Display/ILI9341Display.h>
#include <iostream>
#include <cstdlib>
#include <ctime>


using namespace ELE3312;

Game snakeGame;

/** @brief main function of the game.
  * @param [in] handles A pointer to a structure with peripheral handles from the HAL.
  */
 void cpp_main(peripheral_handles *handles) {

	 snakeGame.setup(handles);
	 snakeGame.inputMenu();
	 HAL_Delay(1000);
	 snakeGame.gameModeMenu();

	 std::srand(HAL_GetTick()); // seed with current time, should be pseudo-random after running snakeGame.menu()
   
	 snakeGame.run();
	 snakeGame.gameOver();

	 while(1) {}

}


