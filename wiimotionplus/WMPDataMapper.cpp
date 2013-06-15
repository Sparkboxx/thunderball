#include "WMPDataMapper.h"

WMPDataMapper::WMPDataMapper(Gyro* g){
  gyro_mapper = new WMPGyroDataMapper(g);
};

WMPDataMapper::WMPDataMapper(Gyro* g, Nunchuck* n){
  gyro_mapper = new WMPGyroDataMapper(g);
  nunchuck_mapper = new WMPNunchuckDataMapper(n);
};

void WMPDataMapper::map(unsigned char* data){
  if( extension_mapping(data) ){
    nunchuck_mapper->map(data);
  }else{
    gyro_mapper->map(data);
  };
};

bool WMPDataMapper::extension_mapping(unsigned char* data){
  return data[5] & 0x02 == 0;
};
