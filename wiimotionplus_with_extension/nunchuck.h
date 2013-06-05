#ifndef NUNCHUCK_H
#define NUNCHUCK_H

class Nunchuck: public Extension {
  Accelerometer acc;
  Button c,z;
  Stick stick;

  public:
    unsigned char activation_signal();
};

#endif
