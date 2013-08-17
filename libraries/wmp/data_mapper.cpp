#include "data_mapper.h"

DataMapper::DataMapper(Gyro* g){
  gyro_mapper = new GyroDataMapper(g);
};

DataMapper::DataMapper(Gyro* g, Nunchuck* n){
  gyro_mapper = new GyroDataMapper(g);
  nunchuck_mapper = new NunchuckDataMapper(n);
};

void DataMapper::map(unsigned char* data){
  if( extension_mapping(data) ){
    nunchuck_mapper->map(data);
  }else{
    gyro_mapper->map(data);
  };
};

bool DataMapper::extension_mapping(unsigned char* data){
  return (data[5] & 0x02) == 0;
};
