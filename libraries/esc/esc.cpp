/*
  ESC.h - Library for Controlling an ESC
  Created by Wilco van Duinkerken, august 2013
  Released into the public domain.
*/
#include "esc.h"

ESC::ESC(){
};

ESC::ESC(Servo* servo, int power_pin, int min_value, int max_value){
  _armed = 0;
  _speed = 0;
  _range = 0;
  _servo = servo;
  _power_pin = power_pin;
  _min_value = min_value;
  _max_value = max_value;
  _range = _max_value - _min_value;
  pinMode(power_pin, OUTPUT);
}

void ESC::calibrate(){
  power_down();
  delay(200);
  _servo->write(_max_value);
  power_up();
  delay(2000);
  arm();
}

void ESC::power_up(){
  digitalWrite(_power_pin, HIGH);
};

void ESC::power_down(){
  digitalWrite(_power_pin, LOW);
}

void ESC::arm(){
  if(_armed==1){
    return;
  }else{
    set_abs_speed(_min_value);
    power_up();
    _armed = 1;
  }
}

void ESC::disarm(){
  set_abs_speed(_min_value);
  power_down();
  _armed = 0;
}

void ESC::increase(float diff){
  if(diff < 0){ diff = 0;}
  if(diff > 1){ diff = 1;}
  change(diff);
}

void ESC::decrease(float diff){
  if(diff > 0){ diff = 0;}
  if(diff < -1){ diff = -1;}
  change(diff);
}

void ESC::change(float diff){
  if(diff > 1){ diff = 1;}
  if(diff < -1){ diff = -1;}
  int new_speed = (int) (_speed - _min_value) * (1.0+diff);
  set_abs_speed(new_speed);
}

void ESC::set_speed(float percentage){
  if(percentage > 1){ percentage = 1;}
  if(percentage < 0){ percentage = 0;}

  int new_speed = _range * percentage + _min_value;
  set_abs_speed(new_speed);
}

int ESC::set_abs_speed(int new_speed){
  if(new_speed < _min_value){
    new_speed = _min_value;
  }

  if(new_speed > _max_value){
    new_speed = _max_value;
  }
  _speed = new_speed;
  _servo->write(_speed);
  return _speed;
}
