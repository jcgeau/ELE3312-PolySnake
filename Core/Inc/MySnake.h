/*
 * MySnake.h
 *
 *  Created on: Oct 3, 2025
 *      Author: jcgauthier
 */

#ifndef SRC_MYSNAKE_H_
#define SRC_MYSNAKE_H_

#include "tile.h"
#include <cstdlib>
#include <ctime>
#include <NucleoImp/Display/ILI9341Display.h>


namespace ELE3312 {

class MySnake {
public:
	MySnake();
	virtual ~MySnake();

	void display();
	void move(int eat);
	void turn(int direction);


private:
	tile snake[100];
	int head{0};
	int tail{0};
	ILI9341Display display;


};

} // End of namespace ELE3312

#endif /* SRC_MYSNAKE_H_ */
