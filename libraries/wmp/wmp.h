/*
 Authors:  Michalis Agathos, Wilco van Duinkerken

 Code based on the ideas and code of:
 http://randomhacksofboredom.blogspot.com/2009/07/motion-plus-and-nunchuck-together-on.html
*/

#ifndef WMP_H
#define WMP_H

#include "gyro.h"
#include "accelerometer.h"
#include "nunchuck.h"
#include "classic_controller.h"
#include "extensions.h"

#include "wire_transfer.h"

#include "data_mapper.h"
#include "gyro_data_mapper.h"
#include "nunchuck_data_mapper.h"

/*
  The Wii MotionPlus (wm+ or WMP) uses i2c (Inter-Integrated Circuits) for all of its communications.
  Depending on the board you use you have to connect the WM+ to different pins.
  Check the Wire library reference to find which pins you have to connect the WM+ to.
  You can find there reference here:

  http://www.arduino.cc/en/Reference/Wire

  For the Arduino Uni it is: A4(SDA) and A5(SCL)

  The reference makes note of the SDA and the SCL pins. You can see which pins
  this are on the WM+ by looking here:

  http://wiibrew.org/wiki/Wiimote/Extension_Controllers

*/

class WMP {
  bool extension_connected;
  WireTransfer *communicator;
  DataMapper *mapper;

  public:
    Extension* extension;
    Nunchuck* nunchuck;
    WMP();
    void initialize();
    Gyro* gyro;

    // Since we have to handle both the connection of an extension as well as
    // the extension connected bool, we use a function for it all.
    void attach_extension(Extension*);
    void attach_nunchuck(Nunchuck*);

    // check if an extension (nunchuck or classic controller)
    // is connected to the wii-motion plus. returns true if an extension is
    // connected and false if an extension is not connected.
    void set_extension_connected(bool);

    // Specifies the activation signal of the WMP, which depends on if an
    // extension is connected, and if it's connected, which one is connected.
    unsigned char activation_signal();

    // Due to a missing way of normal delegation, we'll to it this way
    void turn_on();

    // Get the latest data from the communicator and map it to the WMP
    // structure.
    void update();

};

#endif
