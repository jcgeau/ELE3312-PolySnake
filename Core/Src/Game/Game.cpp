/*
 * Game.cpp
 *
 *      Author: jcgauthier 2212198
 *      		abdul ershad abdul ali 2285559
 */

#include "Game/Game.h"

#include "NucleoImp/SerialCom/SerialFrame.h"

namespace ELE3312 {

ILI9341Display Game::display_;
MPU6050MotionInput Game::motionInput_;
GPIOKeypad Game::keypad_;
UART Game::uart;
DACSound Game::sound_;

Menu Game::menu_;
SnakeGame Game::snakeGame_;

// uart
Ringbuffer Game::uartBuffer;
uint8_t Game::buff[BUFFER_SIZE] = {0};

Game::Game() {}

Game::~Game() {}

/**
 * @brief initialise tout les périphériques pour nous permettres de les utiliser
 * par la suite
 *
 * @param handles
 */
void Game::setup(peripheral_handles* handles) {
  this->handles_ = handles;
  display_.setup(handles->hspi_tft);
  motionInput_.setup(handles->hi2c);
  keypad_.setup(handles->gpio_keypad);
  uart.setup(handles->huart, 5);
  sound_.setup(handles->hdac, handles->htim_dac, 84000000UL);

  menu_.setup(&display_, &keypad_, &uart);
  snakeGame_.setup(&display_, &motionInput_, &keypad_, &uart);

  // fruits_.setup(&display_);
  uartBuffer.setup();

  display_.clearScreen();
  display_.drawString(0, 0, "2212198, 2285559", Color::WHITE);
}

/**
 * @brief affiche la partie du jeux de snake, ou on peut bouger le serpent,
 * manger des fruits et perdre la partie
 *
 */
void Game::run() {
  SerialFrame frame;

  while (1) {
    if (sound_.needUpdate) {
      updateSound();
      sound_.needUpdate = false;
    }

    // Check UART and dispatch messages
    if (uartBuffer.read(buff, BUFFER_SIZE) != 0) {
      frame.setMessage(buff, BUFFER_SIZE);

      switch (frame.getMessageType()) {
        case MessageType::PlayerChoice:
          if (state_ == GameState::Menu) {  // Only dispatch messages for the
                                            // current state
            menu_.handleRemote(frame.getCommTypeMessage());
          }
          break;

        case MessageType::Direction:
          if (state_ == GameState::SnakeGame) {  // Only dispatch messages for
                                                 // the current state
            snakeGame_.handleRemote(frame.getSnakeMessage());
          }
          break;

        case MessageType::Winner:
          if (state_ == GameState::SnakeGame) {  // Only dispatch messages for
                                                 // the current state
            winGame(frame.getVictoryMessage());
          }

        default:
          break;
      }
    }

    // Handle user input
    switch (state_) {
      case GameState::Menu:
        keypad_.update();
        break;
      case GameState::SnakeGame:
        keypad_.update();
        motionInput_.update();
        break;
      case GameState::VictoryScreen:
        break;
      default:
        break;
    }

    // Handle game states
    switch (state_) {
      case GameState::Menu:
        if (menu_.run()) {
          commType_ = menu_.getType();
          state_ = GameState::SnakeGame;
        }
        break;

      case GameState::SnakeGame:
        if (snakeGame_.run(commType_)) state_ = GameState::VictoryScreen;

        break;

      case GameState::VictoryScreen:
        gameOver();
        break;

      default:
        break;
    }

    HAL_Delay(1);
  }
}

/**
 * @brief affichage de l'écran quand la partie est perdu
 *
 */
void Game::gameOver() {
  display_.clearScreen();
  display_.drawString(30, 0, "2212198 & 2285559", Color::WHITE);
  display_.drawString(120, 160, "GAME OVER", Color::RED);
  state_ = GameState::Idle;
}

/**
 * @brief affichage de l'écran quand la partie est gagné
 *
 */
void Game::winGame(VictoryMessage msg) {
  if ((!msg.isValid()) || (msg.getWinner() == Winner::Unknown)) {
    return;
  }

  display_.clearScreen();
  display_.drawString(30, 0, "2212198 & 2285559", Color::WHITE);
  display_.drawString(120, 160, "WINNER", Color::GREEN);
  state_ = GameState::Idle;
}

/** @brief Method that takes data provided by the uart interrupt.
 * @details The received data is stored internally and complete messages are
 * dispatched to the corresponding game sections.
 * @param [in] data A byte of data received from the serial interface.
 */
void Game::handleUART(uint8_t data) { uartBuffer.write(&data, 1); }

/** @brief Method that takes data provided by the uart interrupt.
 * @details The received data is stored internally and complete messages are
 * dispatched to the corresponding game sections.
 * @param [in] data A byte array of data received from the serial interface.
 * @param [in] size The number of bytes in the buffer to be written.
 */
void Game::handleUART(uint8_t* data, uint16_t size) {
  uartBuffer.write(data, size);
}

void Game::soundInit() {
  sound_.setNote(melody[0].note);
  sound_.enableSound();
}

void Game::updateSound() { sound_.update(); }

void Game::setNote() {
  index = (index + 1) % 32;
  sound_.setNote(melody[index].note);
  sound_.needUpdate = true;
}


bool Game::waitSound() {
  soundDelay++;

  if (soundDelay >= melody[index].duration) {
    soundDelay = 0;
    return true;

  } else {
    return false;
  }
}

}  // namespace ELE3312
