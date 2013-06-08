#include "nunchuck.h"

unsigned char Nunchuck::activation_signal(){
  return 0x05;
};

void Nunchuck::set_butt_c(bool value){
  c = (Button) value;
};

void Nunchuck::set_butt_z(bool value){
  z = (Button) value;
};

/* Sets analog stick x-y values in [-1,1] */
void Nunchuck::set_analog(int value_x, int value_y){
  stick.x = 2.*((float) value_x / NUNCHUCK_ANALOG_MAX) - 1.;
  stick.y = 2.*((float) value_y / NUNCHUCK_ANALOG_MAX) - 1.;
};
