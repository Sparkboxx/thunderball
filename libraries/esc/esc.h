/*
  ESC.h - Library for Controlling an ESC
  Created by Wilco van Duinkerken, august 2013
  Released into the public domain.
*/

#ifndef ESC_H
#define ESC_H

#include <Arduino.h>
#include <Servo.h>

class ESC {
  int _speed, _power_pin;
  int _min_value, _max_value, _range;
  Servo* _servo;
  bool _armed;

  public:
    ESC();
    ESC(Servo*, int, int, int);

    // Turn on the Engine at it's lowest speed
    void arm();

    // Turn off the engine
    void disarm();

    // Go through the throttle calibration procedure. Teaching the
    // esc the min and max values of the throttle.
    void calibrate();

    // Increase speed by a percentage expressed as a float 0..1
    // If a value is given outside of this range the function
    // processes the max/min value instead.
    void increase(float);

    // Decrease speed by a percentage of the current speed
    // expressed as a float 0..1
    // If a value is given outside of this range the function
    // processes the max/min value instead.
    void decrease(float);

    // Decrease speed by a percentage of the current speed.
    // Expressed as a float -1..1
    // If a value is given outside of this range the function
    // processes the max/min value instead.
    void change(float);

    // Set the speed as a percentage of total capacity expressed
    // as a float of -1..1.
    // Examples:
    //    set_speed(0.10) puts the engine at 10% of maximum power
    //    set_speed(0.80) puts the engine at 80% of maximum power
    void set_speed(float);

  private:
    // Set the speed of the motor as an absolute value within the
    // ESC range. If a value outside of the min-max range is given
    // the value is processed as being the max or min value possible.
    int set_abs_speed(int);

    // Turn on external power to the ESC
    void power_up();

    // Turn off external power to the ESC
    void power_down();
};

#endif
