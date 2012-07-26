#include "PoombaEngines.h"

const unsigned long int PoombaEngines::BAUD_RATE = 9600;
const unsigned int      PoombaEngines::DEFAULT_SPEED = 15;
const unsigned int      PoombaEngines::REFRESH_ENCODER_FREQ = 20;
const float             PoombaEngines::WHEEL_RADIUS = 4.9;
const float             PoombaEngines::WHEEL_CIRCUMFERENCE = 2 * PI * WHEEL_RADIUS;
const float             PoombaEngines::ROBOT_RADIUS = 12.4;
const float             PoombaEngines::ROBOT_CIRCUMFERENCE = 2 * PI * ROBOT_RADIUS;

const unsigned int PoombaEngines::ACK = 0x00;
const unsigned int PoombaEngines::SET_SPEED_1 = 0x31;
const unsigned int PoombaEngines::SET_SPEED_2 = 0x32;
const unsigned int PoombaEngines::SET_MODE = 0x34;
const unsigned int PoombaEngines::MODE_2 = 0x02;
const unsigned int PoombaEngines::STOP_VALUE = 128;
const unsigned int PoombaEngines::DISABLE_TIMEOUT = 0x38;
const unsigned int PoombaEngines::RESET_ENCODERS = 0x35;
const unsigned int PoombaEngines::GET_ENCODER_1 = 0x23;
const unsigned int PoombaEngines::GET_ENCODER_2 = 0x24;

void PoombaEngines::setup(unsigned long int baudRate) {
  Serial2.begin(baudRate);
  setMode(PoombaEngines::MODE_2); // This library only works with engines in mode 2
  disableTimeout();

  moveForward(2 * PI * WHEEL_RADIUS);
  moveBackward(2 * 2 * PI * WHEEL_RADIUS);
  moveForward(2 * PI * WHEEL_RADIUS);
  turnLeft(90);
  turnRight(180);
  turnLeft(90);
}

void PoombaEngines::moveForward(int length, int speed) {
  resetEncoders();
  double wheelDegrees = length / PoombaEngines::WHEEL_CIRCUMFERENCE * 360;
  while(getEncoder1() < wheelDegrees) {
    setSpeed(PoombaEngines::SET_SPEED_1, PoombaEngines::STOP_VALUE + speed);
    delay(PoombaEngines::REFRESH_ENCODER_FREQ);
    stopEngines();
  }
}

void PoombaEngines::moveBackward(int length, int speed) {
  resetEncoders();
  double wheelDegrees = length / PoombaEngines::WHEEL_CIRCUMFERENCE * 360;
  while(-getEncoder1() < wheelDegrees) {
    setSpeed(PoombaEngines::SET_SPEED_1, PoombaEngines::STOP_VALUE - speed);
    delay(PoombaEngines::REFRESH_ENCODER_FREQ);
    stopEngines();
  }
}

void PoombaEngines::turnLeft(int degrees, int speed) {
  resetEncoders();
  double movementLength = degrees / 360 * PoombaEngines::ROBOT_CIRCUMFERENCE;
  double wheelDegrees = movementLength / PoombaEngines::WHEEL_CIRCUMFERENCE * 360;
  while(-getEncoder1() < wheelDegrees) {
    setSpeed(PoombaEngines::SET_SPEED_1, PoombaEngines::STOP_VALUE);
    setSpeed(PoombaEngines::SET_SPEED_2, PoombaEngines::STOP_VALUE - speed);
    delay(PoombaEngines::REFRESH_ENCODER_FREQ);
    stopEngines();
  }
}

void PoombaEngines::turnRight(int degrees, int speed) {
  resetEncoders();
  double movementLength = degrees / 360 * PoombaEngines::ROBOT_CIRCUMFERENCE;
  double wheelDegrees = movementLength / PoombaEngines::WHEEL_CIRCUMFERENCE * 360;
  while(-getEncoder2() < wheelDegrees) {
    setSpeed(PoombaEngines::SET_SPEED_1, PoombaEngines::STOP_VALUE);
    setSpeed(PoombaEngines::SET_SPEED_2, PoombaEngines::STOP_VALUE + speed);
    delay(PoombaEngines::REFRESH_ENCODER_FREQ);
    stopEngines();
  }
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

void PoombaEngines::resetEncoders() {
  byte resetEncodersMsg [] = {
    PoombaEngines::ACK,
    PoombaEngines::RESET_ENCODERS
  };
  Serial2.write(resetEncodersMsg, sizeof(resetEncodersMsg));
}

long PoombaEngines::getEncoder1() {
  byte getEncoder1Msg [] = {
    PoombaEngines::ACK,
    PoombaEngines::GET_ENCODER_1
  };
  Serial2.write(getEncoder1Msg, sizeof(getEncoder1Msg));

  while(Serial2.available() < 4);
  long result = Serial2.read() << 24;
  result += Serial2.read() << 16;
  result += Serial2.read() << 8;
  result += Serial2.read();

  return result;
}

long PoombaEngines::getEncoder2() {
  byte getEncoder2Msg [] = {
    PoombaEngines::ACK,
    PoombaEngines::GET_ENCODER_2
  };
  Serial2.write(getEncoder2Msg, sizeof(getEncoder2Msg));

  while(Serial2.available() < 4);
  long result = Serial2.read() << 24;
  result += Serial2.read() << 16;
  result += Serial2.read() << 8;
  result += Serial2.read();

  return result;
}