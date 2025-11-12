/**
  * @file FruitMessage.h
  * @date June 2025
  * @brief Declaration of the FruitMessage class that is used to exchange
  * messages in the labyrinth phase of the game.
  * 
  * @defgroup ELE3312
  * @{
  */
#ifndef FRUITMESSAGE_INCLUDE_GUARD
#define FRUITMESSAGE_INCLUDE_GUARD

#include "Interfaces/Communication/Message.h"
#include "tile.h"
#include "Fruits.h"


namespace ELE3312 {
	/** @brief Structure that encapsulates the position data for
	  * a player on the screen.
	  */
	struct FruitMessageData {
		tile fruit;
		int index;
	};

/** @brief The FruitMessage class encapsulates information in the
  * labyrinth phase of the game.
  */
class FruitMessage : public Message {
	public:
		FruitMessage(tile fruit, int index);
		FruitMessage();
		// Setters
		void setType(MessageType newType);
		virtual void setData(uint8_t *newData, size_t length) override;
		// Getters
		MessageType getType();
		virtual size_t getSize() const override;
		virtual const uint8_t *getData() const override;

		virtual std::string toString() const override;

		void setFruit(tile fruit);
		void setIndex(int index);

		tile getFruit() const;
		int getIndex() const;
	private:
		FruitMessageData data;
};

} // End namespace ELE3312

/**
  * @}
  */ // End of the documentation group ELE3312
#endif
