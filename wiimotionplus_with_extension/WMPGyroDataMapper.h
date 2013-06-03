#ifndef WMPGYRODATAMAPPER_H
#define WMPGYRODATAMAPPER_H

#include "wmp.h"
#include "gyro.h"

class WMPGyroDataMapper{
  unsigned char* data;
  WMP* pwmp;
  Gyro* gyro;

  public:
    void set_wmp(WMP* wmp);
    Gyro* gyro();
    void map(unsigned char* new_data);
    int set_yaw();
    int set_pitch();
    int set_roll();
    int set_yaw_slow();
    int set_pitch_slow();
    int set_roll_slow();
    bool set_extension_connected();
};

#endif
