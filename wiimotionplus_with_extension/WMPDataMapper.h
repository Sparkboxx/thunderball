#ifndef WMPDATAMAPPER_H
#define WMPDATAMAPPER_H

#include "wmp.h"
#include "WMPNunchuckDataMapper.h"
#include "WMPGyroDataMapper.h"

class WMPDataMapper{
  WMP* pwmp;
  WMPNunchuckDataMapper nunchuck_mapper;
  WMPGyroDataMapper gyro_mapper;

  public:
    WMPDataMapper(WMP*);
    void map(unsigned char*);
    bool extension_mapping(unsigned char*);
};

#endif
