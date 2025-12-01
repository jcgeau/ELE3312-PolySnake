/*
 * SnakeMessage.cpp
 *
 *      Author: jcgauthier 2212198
 *      		abdul ershad abdul ali 2285559
 */
#ifndef SNAKEMESSAGE_INCLUDE_GUARD
#define SNAKEMESSAGE_INCLUDE_GUARD

#include "Interfaces/Communication/Message.h"
#include "MySnake.h"
#include <string>
#include <iostream>


namespace ELE3312 {

struct SnakeData{
	Direction direction;
	bool turbo;
};

/** @brief The LabyrinthMessage class encapsulates information in the
* labyrinth phase of the game.
*/
class SnakeMessage : public Message {
	public:
		SnakeMessage(Direction direction, bool turbo);
		SnakeMessage();
		// Setters
		void setType(MessageType newType);
		virtual void setData(uint8_t *newData, size_t length) override;
		void setDirection(Direction direction);
		void setTurbo(bool turbo);
		// Getters
		MessageType getType();
		virtual size_t getSize() const override;
		virtual const uint8_t *getData() const override;
		Direction getDirection() const;
		bool getTurbo() const;

		virtual std::string toString() const override;
	private:
		SnakeData data;
};

} // End of namespace ELE3312

/**
  * @}
  */ // End of documentation group ELE3312
#endif
