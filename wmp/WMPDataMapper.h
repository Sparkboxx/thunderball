#ifndef WMPDATAMAPPER_H
#define WMPDATAMAPPER_H

#include "WMPNunchuckDataMapper.h"
#include "WMPGyroDataMapper.h"

class WMPDataMapper {
  WMP* pwmp;
  WMPNunchuckDataMapper* nunchuck_mapper;
  WMPGyroDataMapper* gyro_mapper;

  public:
    WMPDataMapper();
    void map(unsigned char*);
    void set_wmp(WMP*);
    bool extension_mapping(unsigned char*);
};

#endif
