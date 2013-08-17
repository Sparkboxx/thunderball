#include "calibration.h"

void get_calibration_data(int ng, int na, WireTransfer* wire){
  //int ig = 0;  [> gyro calibration data counter <]
  //int ia = 0;  [> accelerometer calibration data counter <]
  //calib_node* gyro_data = NULL;
  //calib_node* acc_data = NULL;
  /*  while (ig < ng || ia < na){
    this_data = wire->read_data();
    if (is_extension){
      add_calibration_data(&gyro_data, this_data);
      ig++;
    }
    else{
      add_calibration_data(&acc_data, this_data);
      ia++;
    }
    }*/
}

void add_calibration_data(struct calib_node** calib_ptr, byte data[6]){
  calib_node* new_node = new calib_node;
  for (int i=0; i<6; i++){
    new_node->data[i] = data[i];
  }
  new_node->next = *calib_ptr;
  *calib_ptr = new_node;
}
/*
  {
  ptr this_ptr;
  this_ptr = calib_ptr;
  while (this_ptr){

  }
  } */
