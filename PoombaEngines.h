#ifndef POOMBA_ENGINES_H
#define POOMBA_ENGINES_H

#include "Arduino.h"

class PoombaEngines
{
public:
  void setup(unsigned long int = PoombaEngines::BAUD_RATE); /** Setup the serial port and the mode */

  /** Movement functions */
  void moveForward(int length, int speed = PoombaEngines::DEFAULT_SPEED);
  void moveBackward(int length, int speed = PoombaEngines::DEFAULT_SPEED);
  void turnLeft(int degrees, int speed = PoombaEngines::DEFAULT_SPEED);
  void turnRight(int degrees, int speed = PoombaEngines::DEFAULT_SPEED);

private:
  /** Engines utility functions */
  void setMode(int mode);
  void setSpeed(int speedType, int speed);
  void stopEngines();
  void disableTimeout();

  /** Generics constants */
  static const unsigned long int BAUD_RATE;
  static const unsigned int DEFAULT_SPEED;

  /** Engines data */
  static const unsigned int ACK;
  static const unsigned int SET_SPEED_1;
  static const unsigned int SET_SPEED_2;
  static const unsigned int SET_MODE;
  static const unsigned int MODE_2;
  static const unsigned int STOP_VALUE;
  static const unsigned int DISABLE_TIMEOUT;
};

#endif