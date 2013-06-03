#ifndef EXTENSIONS_H
#define EXTENSIONS_H

#include "accelerometer.h"

struct Stick {
  int x,y;
}

struct Button {
  int pressed;
}

class Extension {
  public:
    unsigned char activation_signal()=0;
};

class Nunchuck: public Extension {
  Accelerometer acc;
  Button c,z;
  Stick stick;

  public:
    unsigned char activation_signal(){
      return 0x05;
    };
};

class ClassicController: public Extension {
  public:
    unsigned char activation_signal(){
      return 0x05;
    };
};

#endif
