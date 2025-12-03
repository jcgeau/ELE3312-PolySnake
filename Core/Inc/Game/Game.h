/*
 * Game.h
 *
 *  Created on: Oct 22, 2025
 *      Author: jcgauthier 2212198
 *      		abdul ershad abdul ali 2285559
 */

#ifndef SRC_GAME_GAME_H_
#define SRC_GAME_GAME_H_

#include "Fruits.h"
#include "Game/ComMessages/CommTypeMessage.h"
#include "Game/Sections/Menu.h"
#include "Game/Sections/SnakeGame.h"
#include "Interfaces/Keypad/Keypad.h"
#include "MySnake.h"
#include "NucleoImp/Distance/HCSR04Distance.h"
#include "NucleoImp/RGBLight/RGBLED.h"
#include "NucleoImp/Display/ILI9341Display.h"
#include "NucleoImp/Keypad/GPIOKeypad.h"
#include "NucleoImp/MotionInput/MPU6050MotionInput.h"
#include "NucleoImp/SerialCom/Ringbuffer.h"
#include "NucleoImp/SerialCom/SerialFrame.h"
#include "NucleoImp/SerialCom/UART.h"
#include "NucleoImp/Sound/DACSound.h"
#include "cpp_main.h"
#include "main.h"

#define BUFFER_SIZE 128

namespace ELE3312 {

enum class GameState {
  Menu,
  GameModeMenu,
  SnakeGame,
  VictoryScreen,
  Idle

};

enum class ControlMode { INPUT, KEYPAD, GYRO };

class Game {
 public:
  Game();
  virtual ~Game();

  void setup(peripheral_handles* handles);
  void gameModeMenu();

  void initMaster();
  void initSlave();

  void run();
  void gameOver();
  void winGame(VictoryMessage msg);

  void handleUART(uint8_t data);
  void handleUART(uint8_t* data, uint16_t size);
  
  // music functions
  void soundInit();
  void updateSound();
  void setNote();
  bool waitSound();

 private:
  peripheral_handles* handles_ = nullptr;

  static ILI9341Display display_;
  static MPU6050MotionInput motionInput_;
  static GPIOKeypad keypad_;
  static UART uart;
  static DACSound sound_;
  static HCSR04Distance distance_;
  static RGBLED rgbLed_;

  // music
  int index{0};
  int soundDelay{0};

  // uart
  static Ringbuffer uartBuffer;
  static uint8_t buff[];

  static Menu menu_;
  static SnakeGame snakeGame_;

  CommType commType_{CommType::Unknown};
  GameState state_{GameState::Menu};

  MySnake snake_;
  MySnake snakeOpp_;
  Fruits fruits_;
};

} /* namespace ELE3312 */

#endif /* SRC_GAME_GAME_H_ */
