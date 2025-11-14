/*
 * CommTypeMessage.cpp
 *
 *      Author: jcgauthier 2212198
 *      		abdul ershad abdul ali 2285559
 */
#ifndef STRINGMESSAGE_INCLUDE_GUARD
#define STRINGMESSAGE_INCLUDE_GUARD

#include "Interfaces/Communication/Message.h"
#include <string>
#include <iostream>


namespace ELE3312 {

enum class CommType{
	Unknown,
	Master,
	Slave

};

struct CommTypeMessageData{
	CommType type;
	int randSeed;

};

/** @brief The LabyrinthMessage class encapsulates information in the
* labyrinth phase of the game.
*/
class CommTypeMessage : public Message {
	public:
		CommTypeMessage(CommType commType, int randSeed);
		CommTypeMessage();
		// Setters
		void setType(MessageType newType);
		virtual void setData(uint8_t *newData, size_t length) override;
		void setCommType(CommType commType);
		void setRandSeed(int randSeed);
		// Getters
		MessageType getType();
		virtual size_t getSize() const override;
		virtual const uint8_t *getData() const override;
		CommType getCommType() const;
		int getRandSeed() const;

		virtual std::string toString() const override;
	private:
		CommTypeMessageData data;
};

} // End of namespace ELE3312

/**
  * @}
  */ // End of documentation group ELE3312
#endif
