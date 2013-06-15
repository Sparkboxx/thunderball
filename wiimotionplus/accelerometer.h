#ifndef ACCELEROMETER_H
#define ACCELEROMETER_H

#define ACCELEROMETER_MAX 1023

class Accelerometer {
  // Values off the accellerometer
  int acc_x, acc_y, acc_z;

  /* In order to work with the Accelerometer, we have to set the initial value.
   * This will give the initial gravitational acceleration vector and will let us
   * 1) re-express any measured acceleration in g-units
   * 2) combine gyroscope measurement to get absolute acceleration and subtract g
   */

  float acc_x0, acc_y0, acc_z0;
  float g_unit;

  public:
    int calibrate_x(int);
    int calibrate_y(int);
    int calibrate_z(int);
    void calibrate(int, int, int);
    void set_g_unit();

    void set_x(int);
    void set_y(int);
    void set_z(int);
};

#endif

