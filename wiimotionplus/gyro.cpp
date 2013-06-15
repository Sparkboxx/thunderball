#include "gyro.h"

void Gyro::set_yaw(int value){
  yaw = value - yaw0;
};

void Gyro::set_pitch(int value){
  pitch = value - pitch0;
};

void Gyro::set_roll(int value){
  roll = value - roll0;
};

void Gyro::set_yaw_slow(bool value){
  yaw_slow = value;
};

void Gyro::set_pitch_slow(bool value){
  pitch_slow = value;
};

void Gyro::set_roll_slow(bool value){
  roll_slow = value;
};
