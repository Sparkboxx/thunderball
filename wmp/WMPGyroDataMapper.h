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
    void map(unsigned char* new_data);
    void parse_yaw();
    void parse_pitch();
    void parse_roll();
    void parse_yaw_slow();
    void parse_pitch_slow();
    void parse_roll_slow();
    bool set_extension_connected();
};

#endif
