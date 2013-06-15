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

/* This function will gather at least na and ng pieces of data from 
 * the communicator and store them into linked lists for the
 * gyro and accelerometer.
 */
void get_calibration_data(int, WMPWireTransfer*);

void add_calibration_data(struct calib_node*, byte);

/* This function will calibrate the gyro, given the 
 * calibration data list.
 */
void calibrate_gyro(calib_node*, WMPGyroDataMapper*);

/* This function will calibrate the gyro, given the 
 * calibration data list.
 */
void calibrate_accelerometer(calib_node*, WMPNunchuckDataMapper*);

#endif
