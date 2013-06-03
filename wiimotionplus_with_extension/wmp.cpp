/*
 Authors:  Michalis Agathos, Wilco van Duinkerken

 Code based on the ideas and code of:
 http://randomhacksofboredom.blogspot.com/2009/07/motion-plus-and-nunchuck-together-on.html
*/

#include "wmp.h"


class Extension {
  public:
    static unsigned char activation_signal(){
      return 0x04;
    };
};

class WMPWireTransfer {
  WMP* pwmp;
  unsigned char* data;

  public:
    WMPWireTransfer(WMP* wmp){
      pwmp = wmp;
    };

    void turn_on(){
      Wire.beginTransmission(0x53);    //WM+ starts out deactivated at address 0x53
      Wire.write(0xfe);                //send 0x07 to address 0xFE to activate WM+
      Wire.write(pwmp->activation_signal);
      Wire.endTransmission();          //WM+ jumps to address 0x52 and is now active
    };

    void send_zero(){
      Wire.beginTransmission(0x52);     //now at address 0x52
      Wire.write(0x00);                 //send zero to signal we want info
      Wire.endTransmission();
    };

    unsigned char* receive_data(){
      send_zero();                     //send zero before each request (same as nunchuck)
      Wire.requestFrom(0x52,6);        //request six bytes from the WM+

      for (int i=0;i<6;i++){
        data[i]=Wire.read();
      };
      return data;
    };
};

class WMP {
  Extension* pextension;
  bool extension_connected;
  WMPWireTransfer communicator;
  WMPDataMapper mapper(&this);

  public:
    Gyro gyro;
    WMP(){
      pextension = 0;
      set_extension_connected(false);
      mapper = new WMPDataMapper(
    }
    // Since we have to handel both the connection of an extension as well as
    // the extension connected bool, we use a function for it all.
    void attach_extension(Extension* pext){
      pextension = pext;
      set_extension_connected(true);
    }

    // check if an extension (nunchuck or classic controller)
    // is connected to the wii-motion plus. returns true if an extension is
    // connected and false if an extension is not connected.
    void set_extension_connected(bool connected){
      extension_connected = connected;
    };

    //Extension* extension(){
      //return pextension;
    //};

    unsigned char activation_signal(){
      if(extension_connected){
        return pextension->activation_signal;
      }else{
        return 0x04;
      };
    };


    // Due to a missing way of normal delegation, we'll to it this way
    void turn_on(){ communicator.turn_on(); };
    void update() { mapper.map(communicator.receive_data()); }

};

class Nunchuck: public Extension {
  Accelerometer acc;
  Button c,z;
  Stick stick;

  public:
    static unsigned char activation_signal(){
      return 0x05;
    };
};

class ClassicController: public Extension {
  public:
    static unsigned char activation_signal(){
      return 0x05;
    };
};

// BIG FAT TODO
//class ClassicController { };


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

class WMPGyroDataMapper{
  unsigned char* data;
  WMP* pwmp;

  public:
    void set_wmp(WMP* wmp){
      pwmp = wmp;
    };

    Gyro* gyro(){
      return &(pwmp->gyro);
    };

    void map(unsigned char* new_data){
      data = new_data;
      set_yaw(); set_pitch(); set_roll();
      set_yaw_slow(); set_pitch_slow(); set_roll_slow();
      set_extension_connected();
    };

    int set_yaw(){
      int result = ((data[3]>>2)<<8)+data[0];
      gyro->set_yaw(result);
    };

    int set_pitch(){
      int result = ((data[5]>>2)<<8)+data[2];
      gyro->set_pitch(result);
    };

    int set_roll(){
      int result = ((data[4]>>2)<<8)+data[1];
      gyro->set_roll(result);
    };

    int set_yaw_slow(){
      int result = (data[3] >> 1) & 0x0001;
      gyro->set_yaw_slow(result);
    };

    int set_pitch_slow(){
      gyro->set_pitch_slow(data[3] & 0x0001);
    };

    int set_roll_slow(){
      gyro->set_roll_slow((data[4] >> 1) & 0x0001);
    };

    bool set_extension_connected(){
      pwmp->set_extension_connected(data[4] & 0x0001);
    };
};

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
class WMPNunchuckDataMapper {
  unsigned char *data;
  WMP* pwmp;

  public:
    void map(unsigned char data[]){
    };

    void set_wmp(WMP* wmp){
      pwmp = wmp;
    };
};


class WMPDataMapper{
  WMP* pwmp;
  WMPNunchuckDataMapper nunchuck_mapper;
  WMPGyroDataMapper gyro_mapper;

  public:
    WMPDataMapper(WMP* wmp){
      pwmp = wmp;
      nunchuck_mapper.set_wmp(pwmp);
      gyro_mapper.set_wmp(pwmp);
    };

    void map(unsigned char* data){

      if( extension_mapping(data) ){
        nunchuck_mapper.map(data);
      }else{
        gyro_mapper.map(data);
      };
    };

    bool extension_mapping(unsigned char* data){
      return data[5] & 0x02 == 0;
    };


};
