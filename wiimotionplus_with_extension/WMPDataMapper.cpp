#include "WMPDataMapper.h"

WMPDataMapper::WMPDataMapper(WMP* wmp){
  pwmp = wmp;
  nunchuck_mapper.set_wmp(pwmp);
  gyro_mapper.set_wmp(pwmp);
};

void WMPDataMapper::map(unsigned char* data){
  if( extension_mapping(data) ){
    nunchuck_mapper.map(data);
  }else{
    gyro_mapper.map(data);
  };
};

bool WMPDataMapper::extension_mapping(unsigned char* data){
  return data[5] & 0x02 == 0;
};
