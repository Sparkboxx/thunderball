#include "nunchuck.h"

Nunchuck::Nunchuck(){
  acc = new Accelerometer();
  c.pressed = false;
  c.changed = false;
  z.pressed = false;
  z.changed = false;
};

unsigned char Nunchuck::activation_signal(){
  return 0x05;
};

void Nunchuck::set_butt_c(bool value){
  c.pressed == value ? c.changed = false : c.changed = true;
  c.pressed = (bool) value;
};

void Nunchuck::set_butt_z(bool value){
  z.changed = z.pressed != value;
  z.pressed = (bool) value;
};

/* Sets analog stick x-y values in [-1,1] */
void Nunchuck::set_analog(int value_x, int value_y){
  stick.x = 2.*((float) value_x / NUNCHUCK_ANALOG_MAX) - 1.;
  stick.y = 2.*((float) value_y / NUNCHUCK_ANALOG_MAX) - 1.;
};

void Nunchuck::set_acc_x(int value){
  acc->set_x(value);
};
void Nunchuck::set_acc_y(int value){
  acc->set_y(value);
};
void Nunchuck::set_acc_z(int value){
  acc->set_z(value);
};

/* Accessors */

Button Nunchuck::get_butt_c(){
  return c;
}

Button Nunchuck::get_butt_z(){
  return z;
}

Stick Nunchuck::get_analog(){
  return stick;
}
