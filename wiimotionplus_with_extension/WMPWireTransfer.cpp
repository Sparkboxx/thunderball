#include "WMPWireTransfer.h"

WMPWireTransfer::WMPWireTransfer (WMP* wmp){
  pwmp = wmp;
};

void WMPWireTransfer::turn_on(){
  Wire.beginTransmission(0x53);    //WM+ starts out deactivated at address 0x53
  Wire.write(0xfe);                //send 0x07 to address 0xFE to activate WM+
  Wire.write(pwmp->activation_signal());
  Wire.endTransmission();          //WM+ jumps to address 0x52 and is now active
};

void WMPWireTransfer::send_zero(){
  Wire.beginTransmission(0x52);     //now at address 0x52
  Wire.write(0x00);                 //send zero to signal we want info
  Wire.endTransmission();
};

unsigned char* WMPWireTransfer::receive_data(){
  send_zero();                     //send zero before each request (same as nunchuck)
  Wire.requestFrom(0x52,6);        //request six bytes from the WM+

  for (int i=0;i<6;i++){
    data[i]=Wire.read();
  };
  return data;
};
