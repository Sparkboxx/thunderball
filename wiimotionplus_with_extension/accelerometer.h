#ifdef ACCELEROMETER_H
#define ACCELEROMETER_H

class Accelerometer{
  // Values off the accellerometer
  int x, y, z;

  // In order to work with the Accellerometer, we have to set the initial value. After that
  // all measurements are relative to the values at t=0.
  int x0, y0, z0;

  public:
    int calibrate_x(int);
    int calibrate_y(int);
    int calibrate_z(int);
    void calibrate(int, int, int);
};

#endif
