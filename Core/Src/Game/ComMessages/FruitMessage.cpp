/**
  * @file FruitMessage.cpp
  * @date June 2025
  * @brief This file implements the FruitMessage class that defines
  * messages exchanged in the labyrinth phase of the game.
  * 
  * @defgroup ELE3312
  * @{
  */

#include <Game/ComMessages/FruitMessage.h>

using namespace ELE3312;

/** @brief Constructor for a FruitMessage.
  * @param [in] x The x position of the player sending the message.
  * @param [in] y The y position of the player sending the message.
  * @param [in] isCollision Indicates that a collision with the opponent was detected.
  */
FruitMessage::FruitMessage(tile fruit, int index) : Message{MessageType::Fruit} {
	data.fruit.x = fruit.x;
	data.fruit.y = fruit.y;
	data.fruit.id = fruit.id;
	data.index = index;
}

/** @brief Default constructor.
  * @details The default constructor initializes the coordinates of the
  * the player sending the message to zero.
  */
FruitMessage::FruitMessage() : Message{MessageType::Fruit}{

}

// Setters

/** @brief Sets the type of the message.
  * @param [in] newType the type of the message.
  */
void FruitMessage::setType(MessageType newType){
	type = newType;
}

/** @brief Sets the binary data of the message.
  * @details This method can be used to initialize a message object 
  * by providing the binary representation of it's content and then use
  * the object to access the messages content and thus effectively 
  * deserialize the message object from it's binary representation.
  * @param [in] newData An array of bytes representing the message content.
  * @param [in] length The length of the provided data array.
  */
 void FruitMessage::setData(uint8_t *newData, size_t length) {
	if(length != sizeof(FruitMessageData)){
		return;
	}
	data.fruit.x = ((FruitMessageData*)newData)->fruit.x;
	data.fruit.y = ((FruitMessageData*)newData)->fruit.y;
	data.fruit.id = ((FruitMessageData*)newData)->fruit.id;
	data.index = ((FruitMessageData*)newData)->index;

 }

void FruitMessage::setFruit(tile fruit){
	data.fruit = fruit;
}

void FruitMessage::setIndex(int index){
	data.index = index;
}

// Getters

/** @brief Returns the type of the message.
  * @retval The type of the message as a MessageType enum.
  */
MessageType FruitMessage::getType(){
	return type;
}

/** @brief Returns the size/length of the message.
  * @retval The number of bytes constituting the binary representation of the message.
  */
size_t FruitMessage::getSize() const {
	return sizeof(FruitMessageData);
}

/** @brief Returns a pointer to an array containing the binary representation of the 
  * the message's content.
  * @retval An array containing the binary representation of the message's content.
  */
const uint8_t *FruitMessage::getData() const {
	return (uint8_t *)&data;
}

/** @brief Returns a textual representation of the content of the message.
  * @retval A textual representation of the content of the message.
  */
std::string FruitMessage::toString() const {
	return "[" + std::to_string(data.fruit.x) + ", " + std::to_string(data.fruit.y) + "]";
}

tile FruitMessage::getFruit() const{
	return data.fruit;
}

int FruitMessage::getIndex() const{
	return data.index;
}


/**
  *@}
  */ // End of the ELE3312 documentation group
