#ifndef NUNCHUCK_H
#define NUNCHUCK_H

#include "extensions.h"
//#include "accelerometer.h"

typedef bool Button;

typedef struct
{
  float x;
  float y;
} Stick;

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
