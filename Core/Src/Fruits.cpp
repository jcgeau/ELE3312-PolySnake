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
void Fruits::setup(ILI9341Display *display){
	display_ = display;

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
        fruits_[i].disp(*display_);
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
            // Le fruit est mangé → on le replace ailleurs
            fruits_[i].x = (std::rand() % 32) * 10;
            fruits_[i].y = (std::rand() % 24) * 10;
            return true;
        }
    }
    return false;
}

} /* namespace ELE3312 */
