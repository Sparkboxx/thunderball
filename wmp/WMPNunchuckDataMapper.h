#ifndef WMPNUNCHUCKDATAMAPPER_H
#define WMPNUNCHUCKDATAMAPPER_H

#include "accelerometer.h"

class WMPNunchuckDataMapper {
  unsigned char *data;
  Accelerometer* accel;

  public:
    void map(unsigned char*);
    void parse_acc_x();
    void parse_acc_y();
    void parse_acc_z();
    void parse_butt_c();
    void parse_butt_z();
    void parse_analog_x();
    void parse_analog_y();
};

#endif
