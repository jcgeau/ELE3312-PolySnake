/*
 * Fruits.cpp
 *
 *  Created on: Oct 22, 2025
 *      Author: jcgauthier 2212198
 *      		abdul ershad abdul ali 2285559
 */

#include "Fruits.h"

namespace ELE3312 {

Fruits::Fruits() {}

Fruits::~Fruits() {}

/**
 * @brief assigne l'addresse de l'objet display au snake
 * 
 * @param display pointeur vers l'objet permettant l'affichage des composantes
 */
void Fruits::setup(Display *display, Communication *comm){
	display_ = display;
	comm_ = comm;
}


void Fruits::setFruit(tile fruit, int index){
	fruits_[index].x = fruit.x;
	fruits_[index].y = fruit.y;
	fruits_[index].id = fruit.id;
}

/**
 * @brief génere le nombre de fruits équivalent au paramètre fruitCount
 * 
 */
void Fruits::generateFruits() { //2285559

    for (int i = 0; i < fruitCount_; i++) {
          fruits_[i].x = (std::rand() % 32) * 10;
          fruits_[i].y = (std::rand() % 24) * 10;
          fruits_[i].id = tileType::FRUIT_1;

    }
}


/**
 * @brief affiche tous les fruits actifs dans le tableau de fruits
 * 
 */
void Fruits::displayFruits() { //2285559

    for (int i = 0; i < fruitCount_; i++) {
    	if(fruits_[i].id != tileType::BACKGROUND)
    		fruits_[i].disp(display_);
    }
}

/**
 * @brief generates a new fruit in the tile array
 * 
 */
void Fruits::generateNewFruit(){

	for (int i = 0; i < fruitCount_; i++) {
		if (fruits_[i].id == tileType::BACKGROUND) {
			fruits_[i].x = (std::rand() % 32) * 10;
			fruits_[i].y = (std::rand() % 24) * 10;
			fruits_[i].id = tileType::FRUIT_1;
		}
	}
}

/**
 * @brief vérifie si la tete du serpent entre en colision avec un fruits
 * 
 * @param headTile tuile correspondant a la tête du serpent
 * @return true la tête du serpent est sur un fruit
 * @return false la tête du serrpent n'est pas sur un fruit
 */
bool Fruits::checkEatFruit(tile headTile) { //2285559

    for (int i = 0; i < fruitCount_; i++) {
        if (headTile.x == fruits_[i].x && headTile.y == fruits_[i].y) {
            // Le fruit est mangé → on le delete
        	fruits_[i].id = tileType::BACKGROUND;
            return true;
        }
    }
    return false;
}

/**
 * @brief Implémentation en assembleur de la fonction checkEatFruit
 * 
 */
extern "C" bool checkEatFruit_asm(Fruits *self, tile headTile);

/**
 * @brief  appel de la fonction implémenté en assembleur checkEatFruit
 * 
 * @param headTile tuile correspondant a la tête du serpent
 * @return true la tête du serpent est sur un fruit
 * @return false la tête du serrpent n'est pas sur un fruit
 */
bool Fruits::checkEatFruitV2(tile headTile) {
    return checkEatFruit_asm(this, headTile);
}


} /* namespace ELE3312 */
