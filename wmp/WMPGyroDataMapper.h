#ifndef WMPGYRODATAMAPPER_H
#define WMPGYRODATAMAPPER_H

#define GYRO_MAX 8191

#include "gyro.h"

class WMPGyroDataMapper{
  unsigned char* data;
  Gyro* gyro;
  bool extension_connected;

  public:
    WMPGyroDataMapper(Gyro*);
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
