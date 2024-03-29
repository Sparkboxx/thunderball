# ifndef WMPWIRETRANSFER_H
# define WMPWIRETRANSFER_H


#include "twi.h"
#include "nunchuck.h"
#include "classic_controller.h"
#include "Wire.h"

class WireTransfer {
  unsigned char* data;

  public:
    TwoWire* wire;
    WireTransfer(TwoWire*);

    // Turn on the WMP and it's extensions
    void turn_on(unsigned char);

    // In order to receive info from the WMP we need to be able to send it a
    // zero byte.
    void send_zero();

    // Receive data from the WMP, remember to turn it on first.
    unsigned char* receive_data();
};

# endif
