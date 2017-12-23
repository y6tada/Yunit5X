#ifndef  PixyCAM_hpp
#define  PixyCAM_hpp

#include "mbed.h"
#include "Yunit5X.h"

#define MAX_SINGATURE_NUMBER 10
const uint16_t sync = 0xAA55;

class PixyCAM {
    mbed::RawSerial serial;
    mbed::DigitalOut led;
    
    bool     gate_A = false;
    bool     gate_B = false;
    bool     flip   = false;
    int      count  = 0;
    uint8_t  byte, byte_last;
    uint16_t word;
    void     update();
    void     clearDatas();
    int      xOrigin = 0;
    int      yOrigin = 0;
    
public:
    uint16_t checksum;
    uint16_t signature;
    uint16_t X[MAX_SINGATURE_NUMBER];
    uint16_t Y[MAX_SINGATURE_NUMBER];
    uint16_t Width[MAX_SINGATURE_NUMBER];
    uint16_t Height[MAX_SINGATURE_NUMBER];
    
    PixyCAM();
    void callback();
    void setCenter(int x_origin, int y_origin);
    int  getRadius(int sign);
    int  getDegree(int sign);
};

#endif
