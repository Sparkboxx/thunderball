#ifndef WMP_EXTENSIONS
#define WMP_EXTENSIONS

#include "accelerometer.h"
#include "button.h"
#include "stick.h"

class Extension {
  public:
    virtual unsigned char activation_signal()=0;
};

class Nunchuck: public Extension {
  Accelerometer acc;
  Button c,z;
  Stick stick;

  public:
    static unsigned char activation_signal(){
      return 0x05;
    };
};

class ClassicController: public Extension {
  public:
    static unsigned char activation_signal(){
      return 0x05;
    };
};

#endif
