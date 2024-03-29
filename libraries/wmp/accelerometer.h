#ifndef ACCELEROMETER_H
#define ACCELEROMETER_H

#define ACCELEROMETER_MAX 1023

class Accelerometer {
  // Values off the accellerometer
  int x, y, z;

  /* In order to work with the Accelerometer, we have to set the initial value.
   * This will give the initial gravitational acceleration vector and will let us
   * 1) re-express any measured acceleration in g-units
   * 2) combine gyroscope measurement to get absolute acceleration and subtract g
   */

  float x0, y0, z0;
  float g_unit;

  public:
    int calibrate_x(int);
    int calibrate_y(int);
    int calibrate_z(int);
    void calibrate(int, int, int);
    void set_g_unit();
    float get_g_unit();

    void set_x(int);
    void set_y(int);
    void set_z(int);

    int get_x();
    int get_y();
    int get_z();
};

#endif


