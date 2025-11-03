/**
  * @file GameMessage.h
  * @date June 2025
  * @brief Declaration of the GameMessage class that is used to exchange
  * messages in the Game phase of the game.
  * 
  * @defgroup ELE3312
  * @{
  */
#ifndef GAMEMESSAGE_INCLUDE_GUARD
#define GAMEMESSAGE_INCLUDE_GUARD

#include "Interfaces/Communication/Message.h"
#include "MySnake.h"


namespace ELE3312 {
	/** @brief Structure that encapsulates the position data for
	  * a player on the screen.
	  */
	struct GameMessageData {
		uint16_t x; //!< The x position on the screen in pixels
		uint16_t y; //!< The y position on the screen in pixels
		// CollisionType collision; //!< Indicates that a collision with the opponent was detected
		Direction direction; //!< The direction the player is facing
	};

/** @brief The GameMessage class encapsulates information in the
  * Game phase of the game.
  */
class GameMessage : public Message {
	public:
		GameMessage(uint16_t x, uint16_t y,  Direction direction);
		GameMessage();
		// Setters
		void setType(MessageType newType);
		virtual void setData(uint8_t *newData, size_t length) override;
		// Getters
		MessageType getType();
		virtual size_t getSize() const override;
		virtual const uint8_t *getData() const override;

		virtual std::string toString() const override;


		void setX(uint16_t newX);
		void setY(uint16_t newY);
		// void setCollisionType(CollisionType type);
		void setNumberCoins(uint16_t numberCoins);
		void setDirection(Direction direction);

		uint16_t getX() const;
		uint16_t getY() const;
		// CollisionType getCollisionType() const;
		uint16_t getNumberCoins() const;
		Direction getDirection() const;
	private:
		GameMessageData data;
};

} // End namespace ELE3312

/**
  * @}
  */ // End of the documentation group ELE3312
#endif
