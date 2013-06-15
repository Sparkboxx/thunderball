#ifndef EXTENSIONS_H
#define EXTENSIONS_H

// #include "accelerometer.h"

typedef struct tagStick
{
  float x;
  float y;
} Stick;

typedef struct tagButton {
  bool pressed;
  bool changed;
} Button;

class Extension {
  public:
    virtual unsigned char activation_signal()=0;
};

#endif
