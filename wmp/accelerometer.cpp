#include "accelerometer.h"
#include <math.h>

/*void Accelerometer::calibrate_x(int xdata[N_CALIBRATE]){
  acc_x0 = mean(xdata);
  stdev_x0 = stdev(xdata);
}
*/

void Accelerometer::set_acc_x(int value){
  acc_x = (float) value - (0.5*(ACCELEROMETER_MAX)); // WARNING: Assumes "zero" is at exactly half max
  acc_x /= g_unit;
};

void Accelerometer::set_acc_y(int value){
  acc_y = (float) value - (0.5*ACCELEROMETER_MAX);
  acc_y /= g_unit;
};

void Accelerometer::set_acc_z(int value){
  acc_z = (float) value - (0.5*ACCELEROMETER_MAX);
  acc_z /= g_unit;
};

// TODO: Check if a0 is initialized. Otherwise may cause division by 0.
void Accelerometer::set_g_unit(){
  g_unit = sqrt(acc_x0*acc_x0 + acc_y0*acc_y0 + acc_z0*acc_z0); 
};
