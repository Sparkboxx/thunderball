#ifndef NUNCHUCK_H
#define NUNCHUCK_H

#define NUNCHUCK_ANALOG_MAX 255

#include "extensions.h"
#include "accelerometer.h"

class Nunchuck: public Extension {
  Button c,z;
  Stick stick;

  public:
    Accelerometer* acc;
    Nunchuck();
    unsigned char activation_signal();
    void set_butt_c(bool);
    void set_butt_z(bool);
    void set_analog(int, int);
    void set_acc_x(int);
    void set_acc_y(int);
    void set_acc_z(int);
    
    Button get_butt_c();
    Button get_butt_z();
    Stick get_analog();
};

#endif
