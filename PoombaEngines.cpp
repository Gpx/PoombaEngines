#include "PoombaEngines.h"

const unsigned long int PoombaEngines::BAUD_RATE = 9600;
const unsigned int PoombaEngines::DEFAULT_SPEED = 15;

const unsigned int PoombaEngines::ACK = 0x00;
const unsigned int PoombaEngines::SET_SPEED_1 = 0x31;
const unsigned int PoombaEngines::SET_SPEED_2 = 0x32;
const unsigned int PoombaEngines::SET_MODE = 0x34;
const unsigned int PoombaEngines::MODE_2 = 0x02;
const unsigned int PoombaEngines::STOP_VALUE = 128;
const unsigned int PoombaEngines::DISABLE_TIMEOUT = 0x38;

void PoombaEngines::setup(unsigned long int baudRate) {
  Serial2.begin(baudRate);
  setMode(PoombaEngines::MODE_2); // This library only works with engines in mode 2
  disableTimeout();

  moveForward(5);
  moveBackward(5);
  turnLeft(45);
  turnRight(90);
  turnLeft(45);
}

void PoombaEngines::moveForward(int length, int speed) {  
  setSpeed(PoombaEngines::SET_SPEED_1, PoombaEngines::STOP_VALUE + speed);
  delay(length / 12.5 * 1000);
  stopEngines();
}

void PoombaEngines::moveBackward(int length, int speed) {
  setSpeed(PoombaEngines::SET_SPEED_1, PoombaEngines::STOP_VALUE - speed);
  delay(length / 12.5 * 1000);
  stopEngines();
}

void PoombaEngines::turnLeft(int degrees, int speed) {
  setSpeed(PoombaEngines::SET_SPEED_1, PoombaEngines::STOP_VALUE);
  setSpeed(PoombaEngines::SET_SPEED_2, PoombaEngines::STOP_VALUE - speed);
  delay(((20/90.0) * degrees) / 12.5 * 1000);
  stopEngines();
}

void PoombaEngines::turnRight(int degrees, int speed) {
  setSpeed(PoombaEngines::SET_SPEED_1, PoombaEngines::STOP_VALUE);
  setSpeed(PoombaEngines::SET_SPEED_2, PoombaEngines::STOP_VALUE + speed);
  delay(((20/90.0) * degrees) / 12.5 * 1000);
  stopEngines();
}

void PoombaEngines::setMode(int mode) {
  byte setModeMsg [] = {
    PoombaEngines::ACK,
    PoombaEngines::SET_MODE,
    mode
  };
  Serial2.write(setModeMsg, sizeof(setModeMsg));
}

void PoombaEngines::setSpeed(int speedType, int speed) {
  byte setSpeedMsg [] = {
    PoombaEngines::ACK,
    speedType,
    speed
  };
  Serial2.write(setSpeedMsg, sizeof(setSpeedMsg));
}

void PoombaEngines::stopEngines() {
  setSpeed(PoombaEngines::SET_SPEED_1, PoombaEngines::STOP_VALUE);
  setSpeed(PoombaEngines::SET_SPEED_2, PoombaEngines::STOP_VALUE);
}

void PoombaEngines::disableTimeout() {
  byte disableTimeoutMsg [] = {
    PoombaEngines::ACK,
    PoombaEngines::DISABLE_TIMEOUT
  };
  Serial2.write(disableTimeoutMsg, sizeof(disableTimeoutMsg));
}