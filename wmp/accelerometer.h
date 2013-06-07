#ifdef ACCELEROMETER_H
#define ACCELEROMETER_H

class Accelerometer {
  // Values off the accellerometer
  int acc_x, acc_y, acc_z;

  // In order to work with the Accellerometer, we have to set the initial value. After that
  // all measurements are relative to the values at t=0.
  int acc_x0, acc_y0, acc_z0;

  public:
    int calibrate_x(int);
    int calibrate_y(int);
    int calibrate_z(int);
    void calibrate(int, int, int);

    void set_acc_x(int);
    void set_acc_y(int);
    void set_acc_z(int);
};

#endif


