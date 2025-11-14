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


/** @brief The LabyrinthMessage class encapsulates information in the
* labyrinth phase of the game.
*/
class SnakeMessage : public Message {
	public:
		SnakeMessage(Direction direction);
		SnakeMessage();
		// Setters
		void setType(MessageType newType);
		virtual void setData(uint8_t *newData, size_t length) override;
		// Getters
		MessageType getType();
		virtual size_t getSize() const override;
		virtual const uint8_t *getData() const override;
		Direction getDirection() const;

		virtual std::string toString() const override;
	private:
		Direction direction;
};

} // End of namespace ELE3312

/**
  * @}
  */ // End of documentation group ELE3312
#endif
