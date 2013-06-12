#include "Arduino.h"

#include "utility/Wire.h"
#include <wmp.h>

WMP* wmp = new WMP();

void setup(void) {
  Nunchuck* nunchuck = new Nunchuck();

  wmp->initialize();
  wmp->attach_extension(nunchuck);
  wmp->turn_on();
}

void loop(void) {
  wmp->update();
  delay(100);
}
