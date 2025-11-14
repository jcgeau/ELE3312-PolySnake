/*
 * VictoryMessage.cpp
 *
 *      Author: jcgauthier 2212198
 *      		abdul ershad abdul ali 2285559
 */
#include "Game/ComMessages/VictoryMessage.h"
using namespace ELE3312;

/** @brief Constructor for the VictoryMessage class.
  * @param [in] Winner the winner of the game, remote or local
  */
VictoryMessage::VictoryMessage(Winner winner) : Message{MessageType::Winner},
	winner{winner} {
}

/** @brief Default constructor for the VictoryMessage class.
  */
VictoryMessage::VictoryMessage() : Message{MessageType::Winner}, winner{Winner::Unknown} {}

// Setters

/** @brief Sets the type of the message.
  * @param [in] newType The type of the message.
  */
void VictoryMessage::setType(MessageType newType){
	type = newType;
}

/** @brief Sets the contents of the message by providing it's binary representation.
  * @param [in] newData A pointer to an array of bytes containing the binary representation of the message's data.
  * @param [in] length The number of bytes contained in the specified array of bytes.
  */
void VictoryMessage::setData(uint8_t *newData, size_t length){
	if (length < sizeof(Winner)){
		winner = Winner::Unknown;
		return;
	}
	winner = *(Winner*)newData;
}

// Getters

/** @brief Returns the type of the message.
  * @retval The type of the message.
  */
MessageType VictoryMessage::getType(){
	return type;
}

/** @brief Returns the size of the message.
  * @retval The number of bytes contained in the binary representation of the message's content.
  */
size_t VictoryMessage::getSize() const{
	return sizeof(Winner);
}

/** @brief Returns the binary representation of the message's content.
  * @retval An array of bytes representing the contents of the message.
  */
const uint8_t *VictoryMessage::getData() const{
	return  (uint8_t*)&winner;
}

/** @brief Returns a textual representation of the message's content.
  * @retval A text string containing the message's content.
  */
std::string VictoryMessage::toString() const{
	switch(winner){
		case Winner::Winner :
			return "Winner";
		case Winner::Unknown:
		default :
			return "Unknown";

	}
	return "Unknown";
}

/**
 * @brief returns the winner of the game
 * 
 * @return Winner local, remote or unknown
 */
Winner VictoryMessage::getWinner() const{
	return winner;
}

/**
  *@}
  */ //End of documentation group ELE3312




