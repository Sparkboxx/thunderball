#ifndef WMPGYRODATAMAPPER_H
#define WMPGYRODATAMAPPER_H

#include "gyro.h"

class WMPGyroDataMapper{
  unsigned char* data;
  Gyro* gyro;
  bool extension_connected;

  public:
    WMPGyroDataMapper(Gyro*);
    void map(unsigned char* new_data);
    int set_yaw();
    int set_pitch();
    int set_roll();
    int set_yaw_slow();
    int set_pitch_slow();
    int set_roll_slow();
    void set_extension_connected();
};

#endif
