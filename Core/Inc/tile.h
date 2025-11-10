/*
 * tile.h
 *
 *  Created on: Sep 15, 2025
 *      Author: jean-christophe gauthier & ershad abdul ali
 */

#ifndef INC_TILE_H_
#define INC_TILE_H_

#include <NucleoImp/Display/ILI9341Display.h>

namespace ELE3312{

// dimensions for a tile
constexpr uint16_t tileWidth{10};
constexpr uint16_t tileHeight{10};

// enum to clarify id type in tile struct
enum class tileType {
	BACKGROUND,
	SNAKE_HEAD,
	SNAKE_BODY,
	FRUIT_1,
	FRUIT_2

};



struct tile {

	uint16_t x; // horizontal position
	uint16_t y; // vertical position
	tileType id; // corresponding tile to display

	// method to match an id to a color
	Color idColor(tileType id){

		Color color = Color::BLACK;

		switch (id){
			case tileType::BACKGROUND: color = Color::BLACK; break;
			case tileType::SNAKE_HEAD: color = Color::YELLOW;break;
			case tileType::SNAKE_BODY: color = Color::GREEN; break;
			case tileType::FRUIT_1: color = Color::RED; break;
			case tileType::FRUIT_2: color = Color::CYAN; break;
		}

		return color;
	};

	// method to display a single tile
	void disp(Display* display){
		display->fillRect( this->idColor(this->id) , this->x , this->y , tileWidth , tileHeight );
	}

	void erase(Display* display){
		display->fillRect( Color::BLACK , this->x , this->y , tileWidth , tileHeight );
	}

};

}

#endif /* INC_TILE_H_ */
