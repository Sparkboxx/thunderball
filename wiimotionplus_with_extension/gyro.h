#ifndef GYRO_H
#define GYRO_H

/*
  The Wii MotionPlus (wm+ or WMP) uses i2c (Inter-Integrated Circuits) for all of its communications.
  Depending on the board you use you have to connect the WM+ to different pins.
  Check the Wire library reference to find which pins you have to connect the WM+ to.
  You can find there reference here:

  http://www.arduino.cc/en/Reference/Wire

  The reference makes note of the SDA and the SCL pins. You can see which pins
  this are on the WM+ by looking here:

  http://wiibrew.org/wiki/Wiimote/Extension_Controllers

*/


class Gyro{
  // Basic values of the Gyro in the wii-motion plus
  int yaw, pitch, roll;

  // In order to work with the Gyro, we have to set the initial value. After that
  // all measurements are relative to the values at t=0.
  int yaw0, pitch0, roll0;

  // Indicates if the movement in one or more of the directions is slow.
  bool yaw_slow, pitch_slow, roll_slow;

  public:
    int calibrate_yaw(int);
    int calibrate_pitch(int);
    int calibrate_roll(int);

    void calibrate(int, int, int);
    void set_yaw(int);
    void set_pitch(int);
    void set_roll(int);
    void set_yaw_slow(bool);
    void set_pitch_slow(bool);
    void set_roll_slow(bool);
};

#endif
