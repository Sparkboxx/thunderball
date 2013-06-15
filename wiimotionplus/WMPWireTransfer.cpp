#include "Wire2.h"
#include "WMPWireTransfer.h"

WMPWireTransfer::WMPWireTransfer(TwoWire* w){
  wire = w;
};

void WMPWireTransfer::turn_on(unsigned char signal){
  wire->beginTransmission(0x53);    //WM+ starts out deactivated at address 0x53
  wire->write(0xfe);                //send 0x07 to address 0xFE to activate WM+
  wire->write(signal);
  wire->endTransmission();          //WM+ jumps to address 0x52 and is now active
};

void WMPWireTransfer::send_zero(){
  wire->beginTransmission(0x52);     //now at address 0x52
  wire->write(0x00);                 //send zero to signal we want info
  wire->endTransmission();
};

unsigned char* WMPWireTransfer::receive_data(){
  send_zero();                     //send zero before each request (same as nunchuck)
  wire->requestFrom(0x52,6);        //request six bytes from the WM+

  for (int i=0;i<6;i++){
    data[i]=wire->read();
  };
  return data;
};
