# ifndef WMPWIRETRANSFER_H
# define WMPWIRETRANSFER_H

#include "wmp.h"
#include "utility/Wire.h"

class WMPWireTransfer {
  WMP* pwmp;
  unsigned char* data;

  public:
    // Initialize the WMPWireTransfer with a pointer the to the WMP it transfers
    // information for.
    WMPWireTransfer(WMP*);

    // Turn on the WMP and it's extensions
    void turn_on();

    // In order to receive info from the WMP we need to be able to send it a
    // zero byte.
    void send_zero();

    // Receive data from the WMP, remember to turn it on first.
    unsigned char* receive_data();
};

# endif
