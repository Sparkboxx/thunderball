#ifndef NUNCHUCK_H
#define NUNCHUCK_H

#define NUNCHUCK_ANALOG_MAX 255

#include "extensions.h"
// #include "accelerometer.h"

class Nunchuck: public Extension {
  //Accelerometer acc;
  Button c,z;
  Stick stick;

  public:
    unsigned char activation_signal();
    void set_butt_c(bool);
    void set_butt_z(bool);
    void set_analog(int, int);
};

#endif
