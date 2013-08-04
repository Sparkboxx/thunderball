#ifndef WMPNUNCHUCKDATAMAPPER_H
#define WMPNUNCHUCKDATAMAPPER_H

#include "gyro.h"
#include "accelerometer.h"
#include "nunchuck.h"

class WMPNunchuckDataMapper {
  unsigned char* data;
  Nunchuck* nunchuck;

  public:
    WMPNunchuckDataMapper(Nunchuck*);
    void map(unsigned char*);
    void parse_acc_x();  // Q: Should we contract all parse_acc_i to a single one?
    void parse_acc_y();  //    Also write acceleration as a 3-vector?
    void parse_acc_z();
    void parse_butt_c();
    void parse_butt_z();
    void parse_analog();
};

#endif
