#include "wmp.h"

WMP::WMP (){
  extension = 0;
  nunchuck = 0;
  extension_connected = false;
};

void WMP::initialize(){
  TwoWire* wire = new TwoWire();
  gyro = new Gyro();

  communicator = new WMPWireTransfer(wire);
  mapper = new WMPDataMapper(gyro);
};

void WMP::attach_extension(Extension* pext){
  extension = pext;
  set_extension_connected(true);
};

void WMP::attach_nunchuck(Nunchuck* nun){
  nunchuck = nun;
  set_extension_connected(true);
};

void WMP::set_extension_connected(bool connected){
  extension_connected = connected;
};

unsigned char WMP::activation_signal(){
  if(extension_connected){
    return extension->activation_signal();
  }else{
    return 0x04;
  };
};

void WMP::turn_on(){
  communicator->turn_on(activation_signal());
};

void WMP::update() {
  mapper->map(communicator->receive_data());
};
