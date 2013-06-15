# ifndef WMPWIRETRANSFER_H
# define WMPWIRETRANSFER_H


#include "nunchuck.h"
#include "classic_controller.h"
#include "Wire2.h"

class WMPWireTransfer {
  unsigned char* data;
  TwoWire* wire;

  public:
    WMPWireTransfer(TwoWire*);

    // Turn on the WMP and it's extensions
    void turn_on(unsigned char);

    // In order to receive info from the WMP we need to be able to send it a
    // zero byte.
    void send_zero();

    // Receive data from the WMP, remember to turn it on first.
    unsigned char* receive_data();
};

# endif
