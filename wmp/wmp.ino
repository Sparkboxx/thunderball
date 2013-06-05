#include <wmp.h>

WMP wmp;

void setup() {
  wmp = new WMP();
  wmp.initialize();
  wmp.turn_on();
}

void loop() {
  wmp.receive_data();
  delay(100);
}
