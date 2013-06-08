#ifndef WMPNUNCHUCKDATAMAPPER_H
#define WMPNUNCHUCKDATAMAPPER_H

#define ACCELEROMETER_MAX 1023
#define NUNCHUCK_ANALOG_MAX 255

#include "accelerometer.h"
#include "nunchuck.h"

class WMPNunchuckDataMapper {
  unsigned char *data;
  Accelerometer* accel;
  Nunchuck* nunchuck;

  public:
    void map(unsigned char*);
    void parse_acc_x();  // Q: Should we contract all parse_acc_i to a single one?
    void parse_acc_y();  //    Also write acceleration as a 3-vector?
    void parse_acc_z();
    void parse_butt_c();
    void parse_butt_z();
    void parse_analog_x();
    void parse_analog_y();
};

#endif
