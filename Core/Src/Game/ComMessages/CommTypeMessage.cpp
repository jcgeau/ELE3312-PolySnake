
#include "Game/ComMessages/CommTypeMessage.h"
using namespace ELE3312;

/** @brief Constructor for the CommTypeMessage class.
  * @param [in] CommType The character the player has chosen in the menu (Player1 or Player2).
  * @param [in] randSeed The seed used for the std::srand function to generate random fruits.
  */
CommTypeMessage::CommTypeMessage(CommType commType, int randSeed) : Message{MessageType::PlayerChoice} {
	data.type = commType;
	data.randSeed = randSeed;

}

/** @brief Default constructor for the CommTypeMessage class.
  */
CommTypeMessage::CommTypeMessage() : Message{MessageType::PlayerChoice}{
	data.type = CommType::Unknown;
	data.randSeed = 0;
}

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
	if (length < sizeof(CommTypeMessageData)){
		return;
	}

	data.type = ((CommTypeMessageData*)newData)->type;
	data.randSeed = ((CommTypeMessageData*)newData)->randSeed;
}

/**
 * @brief sets the communication type for the current microcontroler
 * 
 * @param commType Unknown, Master or Slave
 */
void CommTypeMessage::setCommType(CommType commType){
	data.type = commType;
}

/**
 * @brief sets the seed used in the std::srand function
 * 
 * @param randSeed 32 bit integer
 */
void CommTypeMessage::setRandSeed(int randSeed){
	data.randSeed = randSeed;
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
	return sizeof(CommTypeMessageData);
}

/** @brief Returns the binary representation of the message's content.
  * @retval An array of bytes representing the contents of the message.
  */
const uint8_t *CommTypeMessage::getData() const{
	return  (uint8_t*)&data;
}

/** @brief Returns a textual representation of the message's content.
  * @retval A text string containing the message's content.
  */
std::string CommTypeMessage::toString() const{
	return "";
}

/** @brief Returns the character the player has chosen.
  * @retval The chosen character (Player1 or player2).
  */
CommType CommTypeMessage::getCommType() const{
	return data.type;
}

/**
 * @brief returns the seed for the random fruit generation
 * 
 * @return int 
 */
int CommTypeMessage::getRandSeed() const{
	return data.randSeed;
}
/**
  *@}
  */ //End of documentation group ELE3312




