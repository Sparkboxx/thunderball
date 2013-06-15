#include <Wire2.h>
#include "wmp.h"

#define DEBUG_GYRO

WMP* wmp = new WMP();

#ifdef DEBUG_GYRO
void output_gyro(){
  Serial.print("Gyro: ");
  Serial.print(wmp->gyro->get_yaw());
  Serial.print(" - ");
  Serial.print(wmp->gyro->get_pitch());
  Serial.print(" - ");
  Serial.print(wmp->gyro->get_roll());
  Serial.println("");
}

#endif

#ifdef DEBUG_ACC

void output_acc(){
  Serial.print(wmp->nunchuck->acc->get_x());
  Serial.print(" - ");
  Serial.print(wmp->nunchuck->acc->get_y());
  Serial.print(" - ");
  Serial.print(wmp->nunchuck->acc->get_z());
}

#endif

void setup(void) {
  Serial.begin(9600);
  Serial.println("There we go...");
  wmp->initialize();
  Serial.println("Initialized WMP");
#ifdef NUNCHUCK_ATTACHED
  Nunchuck* nunchuck = new Nunchuck();
  Serial.println("Initialized Nunchuck");
  wmp->attach_nunchuck(nunchuck);
  Serial.println("Attached Nunchuck");
#endif
  Serial.println("Three, Two, One...");
  wmp->turn_on();
  Serial.println("Lift off!!");
}

void loop(void) {
  wmp->update();
#ifdef DEBUG_GYRO
  output_gyro();
#endif
#ifdef DEBUG_ACC
  output_acc();
#endif
  delay(100);
}

