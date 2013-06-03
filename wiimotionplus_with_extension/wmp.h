#ifndef GYRO
#define GYRO

/*
  The Wii MotionPlus (wm+ or WMP) uses i2c (Inter-Integrated Circuits) for all of its communications.
  Depending on the board you use you have to connect the WM+ to different pins.
  Check the Wire library reference to find which pins you have to connect the WM+ to.
  You can find there reference here:

  http://www.arduino.cc/en/Reference/Wire

  The reference makes note of the SDA and the SCL pins. You can see which pins
  this are on the WM+ by looking here:

  http://wiibrew.org/wiki/Wiimote/Extension_Controllers

*/

#include "gyro.h"
#include "accelerometer.h"

struct Button {
  // Button states are true when pressed and false when untouched.
  bool pressed;
};

struct Stick {
  int x,y;
};

#endif
