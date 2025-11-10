/**
  * @file TextMessage.h 
  * @date June 2025
  * @brief Declares the TextMessage class that represents a message
  * object that carries a text string.
  * 
  * @defgroup ELE3312
  * @{
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

/** @brief The LabyrinthMessage class encapsulates information in the
* labyrinth phase of the game.
*/
class CommTypeMessage : public Message {
	public:
		CommTypeMessage(CommType CommType);
		CommTypeMessage();
		// Setters
		void setType(MessageType newType);
		virtual void setData(uint8_t *newData, size_t length) override;
		// Getters
		MessageType getType();
		virtual size_t getSize() const override;
		virtual const uint8_t *getData() const override;
		CommType getCommType() const;

		virtual std::string toString() const override;
	private:
		CommType commType;
};

} // End of namespace ELE3312

/**
  * @}
  */ // End of documentation group ELE3312
#endif
