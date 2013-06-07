# ifndef WMPWIRETRANSFER_H
# define WMPWIRETRANSFER_H

#include <Wire.h>
#include "nunchuck.h"
#include "classic_controller.h"

class WMP;

class WMPWireTransfer {
  WMP* pwmp;
  unsigned char* data;

  public:
    // Turn on the WMP and it's extensions
    void turn_on();

    // Attach a WMP
    void set_wmp(WMP*);

    // In order to receive info from the WMP we need to be able to send it a
    // zero byte.
    void send_zero();

    // Receive data from the WMP, remember to turn it on first.
    unsigned char* receive_data();
};

# endif
