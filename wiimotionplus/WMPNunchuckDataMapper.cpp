#include "wmp.h"
#include "WMPNunchuckDataMapper.h"

/* NUNCHUCK PASS THROUGH MODE (ACCELEROMETER)

as taken from:
http://wiibrew.org/wiki/Wiimote/Extension_Controllers/Wii_Motion_Plus

|------|--------------------------------------------------------------|
|      |                              Bit                             |
|------|--------------------------------------------------------------|
| Byte |  7   |   6   |   5   |   4   |   3   |   2   |   1   |   0   |
|------|--------------------------------------------------------------|
|  0   |                          SX<7:0>                             |
|------|--------------------------------------------------------------|
|  1   |                          SY<7:0>                             |
|------|--------------------------------------------------------------|
|  2   |                          AX<9:2>                             |
|------|--------------------------------------------------------------|
|  3   |                          AY<9:2>                             |
|------|--------------------------------------------------------------|
|  4   |                     AZ<9:3>                          | ext.  |
|      |                                                      | conn- |
|      |                                                      | ected |
|------|--------------------------------------------------------------|
|  5   |   AZ<2:1>    | AY<1> | AX<1> |   C   |  Z    |   0   |   0   |
|------|--------------------------------------------------------------|

*/

void WMPNunchuckDataMapper::map(unsigned char new_data[]){
  data = new_data;
  parse_acc_x(); parse_acc_y(); parse_acc_z();
  parse_butt_c(); parse_butt_z();
  parse_analog();
};

// this should add bit 4 as bit 1 (verify)
void WMPNunchuckDataMapper::parse_acc_x(){
  nunchuck->set_acc_x((data[2] << 2) + ((data[5] >> 3) & 0x0002));
};

// this should add bit 5 as bit 1 (verify)
void WMPNunchuckDataMapper::parse_acc_y(){
  nunchuck->set_acc_y((data[3] << 2) + ((data[5] >> 4) & 0x0002) );
};

// this should add the bit 6 and 7 as bit 1 and 2 (verify)
void WMPNunchuckDataMapper::parse_acc_z(){
  nunchuck->set_acc_z(((data[4] >> 1) << 3) + ((data[5] >> 5) & 0x0006));
};

void WMPNunchuckDataMapper::parse_butt_c(){
  nunchuck->set_butt_c((bool) !!(data[5] & 0x8));
};

void WMPNunchuckDataMapper::parse_butt_z(){
  nunchuck->set_butt_z((bool) !!(data[5] & 0x4));
};

void WMPNunchuckDataMapper::parse_analog(){
  int analog_x = (int) data[0];
  int analog_y = (int) data[1];
  nunchuck->set_analog(analog_x, analog_y);
};

