#ifndef POOMBA_ENGINES_H
#define POOMBA_ENGINES_H

#include "Arduino.h"
#include "PoombaCompass.h"

class PoombaEngines
{
public:
  void setup(unsigned long int = PoombaEngines::BAUD_RATE); /** Setup the serial port and the mode */

  /** Movement functions */
  void moveForward(int length, int speed = PoombaEngines::DEFAULT_SPEED);
  void moveBackward(int length, int speed = PoombaEngines::DEFAULT_SPEED);
  void turnLeft(int degrees, bool test = PoombaEngines::DEFAULT_TEST_BEHAVIOR, int speed = PoombaEngines::DEFAULT_SPEED);
  void turnRight(int degrees, bool test = PoombaEngines::DEFAULT_TEST_BEHAVIOR, int speed = PoombaEngines::DEFAULT_SPEED);

private:
  /** Engines utility functions */
  void setMode(int mode);
  void setSpeed(int speedType, int speed);
  void stopEngines();
  void disableTimeout();
  void resetEncoders();
  long getEncoder1();
  long getEncoder2();

  /** Generics constants */
  static const unsigned long int BAUD_RATE;
  static const unsigned int      DEFAULT_SPEED;
  static const bool              DEFAULT_TEST_BEHAVIOR;
  static const unsigned int      REFRESH_ENCODER_FREQ; // ms
  static const float             WHEEL_RADIUS; // cm
  static const float             WHEEL_CIRCUMFERENCE; // cm
  static const float             ROBOT_RADIUS; // cm
  static const float             ROBOT_CIRCUMFERENCE; // cm

  /** Engines data */
  static const unsigned int ACK;
  static const unsigned int SET_SPEED_1;
  static const unsigned int SET_SPEED_2;
  static const unsigned int SET_MODE;
  static const unsigned int MODE_2;
  static const unsigned int STOP_VALUE;
  static const unsigned int DISABLE_TIMEOUT;
  static const unsigned int RESET_ENCODERS;
  static const unsigned int GET_ENCODER_1;
  static const unsigned int GET_ENCODER_2;

  /** Compass handler */
  PoombaCompass pc;
};

#endif