#ifndef WMPDATAMAPPER_H
#define WMPDATAMAPPER_H

#include "WMPNunchuckDataMapper.h"
#include "WMPGyroDataMapper.h"
#include "gyro.h"

class WMPDataMapper {
  WMPNunchuckDataMapper* nunchuck_mapper;
  WMPGyroDataMapper* gyro_mapper;

  public:
    WMPDataMapper(Gyro*);
    WMPDataMapper(Gyro*, Nunchuck*);
    void map(unsigned char*);
    bool extension_mapping(unsigned char*);
};

#endif
