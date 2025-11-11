/*
 * Menu.h
 *
 *  Created on: Nov 1, 2025
 *      Author: jcgauthier
 */

#ifndef SRC_GAME_SECTIONS_MENU_H_
#define SRC_GAME_SECTIONS_MENU_H_

#include "Interfaces/Display/Display.h"
#include "Interfaces/Keypad/Keypad.h"
#include "Interfaces/Communication/Communication.h"
#include "Game/ComMessages/CommTypeMessage.h"
// #include "Game/ComMessages/PlayerChoiceMessage.h"
#include <memory>

namespace ELE3312 {

/** @brief Represents the different states of the menu phase of the game.
  */
enum class MenuState {
	Initialization, Run
};

/** @brief The Menu class represents the menu that is displayed at the beginning of the game
  * where the player chooses it's game character (PacMan or Ghost).
  */
class Menu {
public:
	Menu();
	void setup(Display *disp, Keypad *keypad, Communication *comm);
	virtual ~Menu() = default;

	CommType getType();

	bool run();

	void handleRemote(CommTypeMessage msg);

private:
	void initialize();
	Display *disp {nullptr};
	Keypad *keypad {nullptr};
	Communication *comm {nullptr};
	bool choiceGhost_{false};
	MenuState state {MenuState::Initialization};
	CommType type {CommType::Unknown};
};

} /* namespace ELE3312 */

#endif /* SRC_GAME_SECTIONS_MENU_H_ */
