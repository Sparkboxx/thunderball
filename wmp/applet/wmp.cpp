#include "Arduino.h"

#include <wmp.h>

WMP* wmp = new WMP();

void setup() {
  Nunchuck* nunchuck = new Nunchuck();

  wmp->initialize();
  wmp->attach_extension(nunchuck);
  wmp->turn_on();
}

void loop() {
  wmp->update();
  delay(100);
}
