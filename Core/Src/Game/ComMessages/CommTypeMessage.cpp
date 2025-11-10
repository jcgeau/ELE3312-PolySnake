/**
  * @file PlayerChoice.cpp
  * @date June 2025
  * @brief This file implements the PlayerChiceMessage class that is used to
  * exchange the player's character choice.
  *
  * @defgroup ELE3312
  * @{
  */
#include "Game/ComMessages/CommTypeMessage.h"
using namespace ELE3312;

/** @brief Constructor for the CommTypeMessage class.
  * @param [in] CommType The character the player has chosen in the menu (Pacman or Ghost).
  */
CommTypeMessage::CommTypeMessage(CommType CommType) : Message{MessageType::PlayerChoice},
	commType{CommType} {
}

/** @brief Default constructor for the CommTypeMessage class.
  */
CommTypeMessage::CommTypeMessage() : Message{MessageType::PlayerChoice}, commType{CommType::Unknown} {}

// Setters

/** @brief Sets the type of the message.
  * @param [in] newType The type of the message.
  */
void CommTypeMessage::setType(MessageType newType){
	type = newType;
}

/** @brief Sets the contents of the message by providing it's binary representation.
  * @param [in] newData A pointer to an array of bytes containing the binary representation of the message's data.
  * @param [in] length The number of bytes contained in the specified array of bytes.
  */
void CommTypeMessage::setData(uint8_t *newData, size_t length){
	if (length < sizeof(CommType)){
		commType = CommType::Unknown;
		return;
	}
	commType = *(CommType*)newData;
}

// Getters

/** @brief Returns the type of the message.
  * @retval The type of the message.
  */
MessageType CommTypeMessage::getType(){
	return type;
}

/** @brief Returns the size of the message.
  * @retval The number of bytes contained in the binary representation of the message's content.
  */
size_t CommTypeMessage::getSize() const{
	return sizeof(CommType);
}

/** @brief Returns the binary representation of the message's content.
  * @retval An array of bytes representing the contents of the message.
  */
const uint8_t *CommTypeMessage::getData() const{
	return  (uint8_t*)&commType;
}

/** @brief Returns a textual representation of the message's content.
  * @retval A text string containing the message's content.
  */
std::string CommTypeMessage::toString() const{
	switch(commType){
		case CommType::Master :
			return "Master";
		case CommType::Slave :
			return "Slave";
		case CommType::Unknown:
		default :
			return "Unknown";

	}
	return "Unknown";
}

/** @brief Returns the character the player has chosen.
  * @retval The chosen character (e.g. PacMan or Ghost).
  */
CommType CommTypeMessage::getCommType() const{
	return commType;
}

/**
  *@}
  */ //End of documentation group ELE3312




