#include "Arduino.h"

#include <Wire.h>
// The WII motion plus and pass-thru options use a 6 byte integer to
// communicate all values and states. See detailed documentation below.
byte data[6];          //six data bytes

bool time_for_nunchuck;

void wiiMotionPlusSendZero(){
}

void calibrateInitialValues(){
  for (int i=0;i<10;i++){
    wiiMotionPlusSendZero();

    Wire.requestFrom(0x52,6);
    for (int i=0;i<6;i++){
      data[i]=Wire.read();
    }

    yaw0+=(((data[3]>>2)<<8)+data[0])/10;        //average 10 readings for each zero
    pitch0+=(((data[4]>>2)<<8)+data[1])/10;
    roll0+=(((data[5]>>2)<<8)+data[2])/10;
  }
}

void receiveData(){

  time_for_nunchuck = data[5] & 0x02;
  ext_on = data[4] & 0x01;


  // NUNCHUCK
  // TODO: Evaluate if ext_on can go out of this if statement
  if (ext_on && time_for_nunchuck){
    // Accellerometer Data
    acc_x=((data[2]<<2)+((data[5] & 0x10) << 1));// - accz0;
    acc_y=((data[3]<<2)+((data[5] & 0x20) << 1));// - accy0;
    acc_z=((data[4] >> 1) << 3)+((data[5] >> 6) << 1); // - accz0;

    // Buttons and joystick data
    button_c = data[5] & 0x08;
    button_z = data[5] & 0x04;

  }else{
    pitch = get_pitch(data) - pitch0;
    yaw = get_yaw(data) - yaw0;
    roll = get_roll(data) - roll0;
  }

}

void setup(){
  Serial.begin(115200);
  Wire.begin();
  wiiMotionPlusOn();
  calibrateInitialValues();
  delay(100);
}

void loop(){
  receiveData();                  //receive data and calculate yaw pitch and roll
  Serial.println("print something here");
  delay(1234);
}

//see diagram on randomhacksofboredom.blogspot.com

/*
Additional Reading:
 The wii motion plus's initialization sequence was pull from here:
 http://wiibrew.org/wiki/Wiimote/Extension_Controllers#Wii_Motion_Plus

 The data format is well documented here:
 http://wiibrew.org/wiki/Wiimote/Extension_Controllers#Data_Format_.28Wii_Motion_Plus.29

 More pinout diagrams can be found here:
 http://wiibrew.org/wiki/Wiimote/Extension_Controllers#Hardware_.28Wii_Motion_Plus.29
*/
#include <wmp.h>

WMP wmp;

void setup() {
  wmp = new WMP();
  wmp.initialize();
  wmp.turn_on();
}

void loop() {
  wmp.receive_data();
  delay(100);
}
