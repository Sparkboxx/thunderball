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

int Gyro::get_yaw(){
  return yaw;
};

int Gyro::get_pitch(){
  return pitch;
};

int Gyro::get_roll(){
  return roll;
};

int Gyro::get_yaw_slow(){
  return yaw_slow;
};

int Gyro::get_pitch_slow(){
  return pitch_slow;
};

int Gyro::get_roll_slow(){
  return roll_slow;
};
