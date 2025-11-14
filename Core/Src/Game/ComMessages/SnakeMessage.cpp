/*
 * SnakeMessage.cpp
 *
 *      Author: jcgauthier 2212198
 *      		abdul ershad abdul ali 2285559
 */
#include "Game/ComMessages/SnakeMessage.h"
using namespace ELE3312;

/** @brief Constructor for the SnakeMessage class.
  * @param [in] Direction Current direction of a MySnake object
  */
SnakeMessage::SnakeMessage(Direction direction) : Message{MessageType::Direction},
	direction{direction} {
}

/** @brief Default constructor for the SnakeMessage class.
  */
SnakeMessage::SnakeMessage() : Message{MessageType::Direction}, direction{Direction::Unknown} {}

// Setters

/** @brief Sets the type of the message.
  * @param [in] newType The type of the message.
  */
void SnakeMessage::setType(MessageType newType){
	type = newType;
}

/** @brief Sets the contents of the message by providing it's binary representation.
  * @param [in] newData A pointer to an array of bytes containing the binary representation of the message's data.
  * @param [in] length The number of bytes contained in the specified array of bytes.
  */
void SnakeMessage::setData(uint8_t *newData, size_t length){
	if (length < sizeof(Direction)){
		direction = Direction::Unknown;
		return;
	}
	direction = *(Direction*)newData;
}

// Getters

/** @brief Returns the type of the message.
  * @retval The type of the message.
  */
MessageType SnakeMessage::getType(){
	return type;
}

/** @brief Returns the size of the message.
  * @retval The number of bytes contained in the binary representation of the message's content.
  */
size_t SnakeMessage::getSize() const{
	return sizeof(Direction);
}

/** @brief Returns the binary representation of the message's content.
  * @retval An array of bytes representing the contents of the message.
  */
const uint8_t *SnakeMessage::getData() const{
	return  (uint8_t*)&direction;
}

/** @brief Returns a textual representation of the message's content.
  * @retval A text string containing the message's content.
  */
std::string SnakeMessage::toString() const{
	switch(direction){
		case Direction::NORTH :
			return "North";
		case Direction::SOUTH :
			return "South";
		case Direction::Unknown:
		default :
			return "Unknown";

	}
	return "Unknown";
}

/**
 * @brief returns the current direction of a MySnake object
 * 
 * @return Direction East, west, south or north
 */
Direction SnakeMessage::getDirection() const{
	return direction;
}

/**
  *@}
  */ //End of documentation group ELE3312




