#ifndef WMPNUNCHUCKDATAMAPPER_H
#define WMPNUNCHUCKDATAMAPPER_H

class WMPNunchuckDataMapper {
  unsigned char *data;
  WMP* pwmp;

  public:
    void map(unsigned char*);
    void set_wmp(WMP*);
};

#endif
