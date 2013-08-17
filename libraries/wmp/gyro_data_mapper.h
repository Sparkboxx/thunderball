#ifndef WMPGYRODATAMAPPER_H
#define WMPGYRODATAMAPPER_H

#define GYRO_MAX 8191

#include "gyro.h"

class GyroDataMapper{
  unsigned char* data;
  Gyro* gyro;
  bool extension_connected;

  public:
    GyroDataMapper(Gyro*);
    void set_gyro(Gyro*);
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
