#include "wmp.h"

WMP::WMP (){
  pextension = 0;
  extension_connected = false;
};

void WMP::initialize(){
  communicator = new WMPWireTransfer;
  communicator->set_wmp(this);

  mapper = new WMPDataMapper;
  mapper->set_wmp(this);
}

void WMP::attach_extension(Extension* pext){
  pextension = pext;
  set_extension_connected(true);
};

void WMP::set_extension_connected(bool connected){
  extension_connected = connected;
};

unsigned char WMP::activation_signal(){
  if(extension_connected){
    return pextension->activation_signal();
  }else{
    return 0x04;
  };
};

void WMP::turn_on(){
  communicator->turn_on();
};

void WMP::update() {
  mapper->map(communicator->receive_data());
};
