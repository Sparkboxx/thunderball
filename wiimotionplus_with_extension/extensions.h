#ifndef EXTENSIONS_H
#define EXTENSIONS_H

#include "accelerometer.h"

struct Stick {
  int x,y;
};

struct Button {
  int pressed;
};

class Extension {
  public:
    virtual unsigned char activation_signal()=0;
};

#endif
