#ifndef WMPDATAMAPPER_H
#define WMPDATAMAPPER_H

#include "nunchuck_data_mapper.h"
#include "gyro_data_mapper.h"
#include "gyro.h"

class DataMapper {
  NunchuckDataMapper* nunchuck_mapper;
  GyroDataMapper* gyro_mapper;

  public:
    DataMapper(Gyro*);
    DataMapper(Gyro*, Nunchuck*);
    void map(unsigned char*);
    bool extension_mapping(unsigned char*);
};

#endif
