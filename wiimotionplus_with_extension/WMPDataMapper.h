#ifndef WMPDATAMAPPER_H
#define WMPDATAMAPPER_H

#include "WMPNunchuckDataMapper.h"
#include "WMPGyroDataMapper.h"

class WMP;

class WMPDataMapper {
  WMP* pwmp;
  WMPNunchuckDataMapper nunchuck_mapper;
  WMPGyroDataMapper gyro_mapper;

  public:
    WMPDataMapper(WMP*);
    void map(unsigned char*);
    bool extension_mapping(unsigned char*);
};

#endif
