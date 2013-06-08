#ifndef WMPNUNCHUCKDATAMAPPER_H
#define WMPNUNCHUCKDATAMAPPER_H

#include "accelerometer.h"
#include "nunchuck.h"

class WMPNunchuckDataMapper {
  unsigned char* data;
  Accelerometer* accel;
  Nunchuck* nunchuck;

  public:
    WMPNunchuckDataMapper(Accelerometer*, Nunchuck*);
    void map(unsigned char*);
    void parse_acc_x();  // Q: Should we contract all parse_acc_i to a single one?
    void parse_acc_y();  //    Also write acceleration as a 3-vector?
    void parse_acc_z();
    void parse_butt_c();
    void parse_butt_z();
    void parse_analog();
};

#endif
