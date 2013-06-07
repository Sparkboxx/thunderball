#ifndef NUNCHUCK_H
#define NUNCHUCK_H

#include "extensions.h"
#include "accelerometer.h"

class Nunchuck: public Extension {
  //Accelerometer acc;
  Button c,z;
  Stick stick;

  public:
    unsigned char activation_signal();
};

#endif
