#include <Wire2.h>
#include "wmp.h"

#define DEBUG

WMP* wmp = new WMP();

#ifdef DEBUG
void output_gyro(){
  Serial.print(wmp->gyro->get_yaw());
  Serial.print(" - ");
  Serial.print(wmp->gyro->get_pitch());
  Serial.print(" - ");
  Serial.print(wmp->gyro->get_roll());
  Serial.println("");
}

void output_acc(){
  Serial.print(wmp->nunchuck->acc->get_x());
  Serial.print(" - ");
  Serial.print(wmp->nunchuck->acc->get_y());
  Serial.print(" - ");
  Serial.print(wmp->nunchuck->acc->get_z());
}
#endif

void setup(void) {
  Nunchuck* nunchuck = new Nunchuck();

  wmp->initialize();
  wmp->attach_nunchuck(nunchuck);
  wmp->turn_on();
}

void loop(void) {
  wmp->update();
#ifdef DEBUG
  output_gyro();
  output_acc();
#endif
  delay(100);
}

