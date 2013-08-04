#include "accelerometer.h"
#include <math.h>

/*void Accelerometer::calibrate_x(int xdata[N_CALIBRATE]){
  x0 = mean(xdata);
  stdev_x0 = stdev(xdata);
}
*/

void Accelerometer::set_x(int value){
  x = (float) value - (0.5*(ACCELEROMETER_MAX)); // WARNING: Assumes "zero" is at exactly half max
  //  x /= g_unit;
};

void Accelerometer::set_y(int value){
  y = (float) value - (0.5*ACCELEROMETER_MAX);
  //y /= g_unit;
};

void Accelerometer::set_z(int value){
  z = (float) value - (0.5*ACCELEROMETER_MAX);
  //z /= g_unit;
};

int Accelerometer::get_x(){
  return x;
};

int Accelerometer::get_y(){
  return y;
};

int Accelerometer::get_z(){
  return z;
};

// TODO: Check if a0 is initialized. Otherwise may cause division by 0.
void Accelerometer::set_g_unit(){
  g_unit = sqrt(x0*x0 + y0*y0 + z0*z0);
};

float Accelerometer::get_g_unit(){
  return g_unit;
}
