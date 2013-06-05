#include "WMPGyroDataMapper.h"

/* DATA FORMAT WII MOTION PLUS (GYRO)

as taken from:
http://wiibrew.org/wiki/Wiimote/Extension_Controllers/Wii_Motion_Plus

** NOTE **

Bit positions count from right to left. So bit position 0 is the most
'right' bit, and bit 13 bit is the most 'left' bit.

this is also why you see the <13:8> position definition in bytes 3,4 and 5.

|------|--------------------------------------------------------------|
|      |                              Bit                             |
|------|--------------------------------------------------------------|
| Byte |  7   |   6   |   5   |   4   |   3   |   2   |   1   |   0   |
|------|--------------------------------------------------------------|
|  0   |                  Yaw Down Speed<7:0>                         |
|------|--------------------------------------------------------------|
|  1   |                  Roll Left Speed<7:0>                        |
|------|--------------------------------------------------------------|
|  2   |                  Pitch Left Speed<7:0>                       |
|------|--------------------------------------------------------------|
|  3   |              Yaw Down Speed<13:8>            | yaw   | pitch |
|      |                                              | slow  | slow  |
|      |                                              | mode  | mode  |
|------|--------------------------------------------------------------|
|  4   |              Roll left speed<13:8>           | roll  | ext.  |
|      |                                              | slow  | conn- |
|      |                                              | mode  | ected |
|------|--------------------------------------------------------------|
|  5   |              Pitch left speed<13:8>          |   1   |   0   |
|------|--------------------------------------------------------------|

*/

/* The YAW, PITCH and ROLL values are 14 bit integers
   (maximum value = 2^14 - 1 = 8191).
   The first 8 bits are available in the first Byte. The last 6 bits are
   available in bits 8 to 13 in byte 3.

   BITWISE OPERATORS
   -----------------

   We have several operators at our displosal to stitch the 2 together.

   the >> operator moves bits to the right so:
   1111 1100 >> 2 becomes
   0011 1111

   the << operator moves bits to the left, so:
   0011 1111 << 8 becomes
   0011 1111 0000 0000 (notice how this now is a 16 bit value)

   by applying the >> 2 and << 8 operators to bit <13:8> of byte 3
   and adding the bits of the first byte, we construct the 'original' value
   of YAW, PITCH or ROLL.

   ADDING INTEGERS
   ---------------

   the addition of "bits" is a bit like rock-paper-scissors:
   - 0 beats nothing (.)
   - 1 beats zero


   EXAMPLE
   -------

   given:
   - a value of bits <13:8> of byte 3 of 1111 1111
   - a value of bits <7:0>  of byte 1 of 0001 1101

   ******* PSEUDO CODE EXAMPLE  **********

   shifted_to_right = (data[3] >> 2)            #=> 0011 1111
   shifted_to_left = shift_to_right << 8        #=> 0011 1111 0000 0000
   yaw = shifted_to_left + data[0]              #=> 0011 1111 0001 1101

   ******** Visual representation of code example above *********

   shift_to_right:
   1111 1111 >> 2         #=> 0011 1111

   shift_to_left:
   0011 1111 << 8         #=> 0011 1111 0000 0000

   add data[0]

   0011 1111 0000 0000
   .... .... 0001 1101  +
   ----------------------
   0011 1111 0001 1101    #=> 16 bit integer YAW value.

*/

void WMPGyroDataMapper::set_wmp(WMP* wmp){
  pwmp = wmp;
  gyro = &(pwmp->gyro);
};

void WMPGyroDataMapper::map(unsigned char* new_data){
  data = new_data;
  set_yaw(); set_pitch(); set_roll();
  set_yaw_slow(); set_pitch_slow(); set_roll_slow();
  set_extension_connected();
};

int WMPGyroDataMapper::set_yaw(){
  int result = ((data[3]>>2)<<8)+data[0];
  gyro->set_yaw(result);
};

int WMPGyroDataMapper::set_pitch(){
  int result = ((data[5]>>2)<<8)+data[2];
  gyro->set_pitch(result);
};

int WMPGyroDataMapper::set_roll(){
  int result = ((data[4]>>2)<<8)+data[1];
  gyro->set_roll(result);
};

int WMPGyroDataMapper::set_yaw_slow(){
  int result = (data[3] >> 1) & 0x0001;
  gyro->set_yaw_slow(result);
};

int WMPGyroDataMapper::set_pitch_slow(){
  gyro->set_pitch_slow(data[3] & 0x0001);
};

int WMPGyroDataMapper::set_roll_slow(){
  gyro->set_roll_slow((data[4] >> 1) & 0x0001);
};

bool WMPGyroDataMapper::set_extension_connected(){
  pwmp->set_extension_connected(data[4] & 0x0001);
};