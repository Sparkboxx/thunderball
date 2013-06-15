#ifndef CALIBRATION_H
#define CALIBRATION_H

#define N_CALIBRATE 10

#include <Arduino.h>
#include "WMPWireTransfer.h"
#include "WMPGyroDataMapper.h"
#include "WMPNunchuckDataMapper.h"

struct calib_node
{
  byte data[6];
  calib_node* next;
};

/* This function will gather N pieces of data from 
 * the communicator and store them into a linked list.
 */
void get_calibration_data(int, WMPWireTransfer*);

/* This function will calibrate the gyro, given the 
 * calibration data list.
 */
void calibrate_gyro(calib_node*, WMPGyroDataMapper*);

/* This function will calibrate the gyro, given the 
 * calibration data list.
 */
void calibrate_accelerometer(calib_node*, WMPNunchuckDataMapper*);

#endif
