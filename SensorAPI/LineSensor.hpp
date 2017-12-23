#ifndef LineSensor_hpp
#define LineSensor_hpp

#include "mbed.h"
#include "Yunit5X.h"

#define bitRead(value, bit) (((value) >> (bit)) & 0x01)

class LineSensor {
    mbed::RawSerial serial;
    uint8_t dataNum   = 0;
    uint8_t FirstSync = 0;
    uint8_t LastSync  = 0;
    uint8_t cash[255];
    int count = 0;
    int cash_data_last = 0;
    void updateSensorStatus(uint8_t HighByte, uint8_t LowByte);
    
public:
    bool FL, FC, FR;
    bool RF, RC, RB;
    bool BR, BC, BL;
    bool LB, LC, LF;
    bool OR;
    
    LineSensor();
    void init(uint8_t dataNum, uint8_t FirstSync, uint8_t LastSync);
    void update(uint8_t data);
};

#endif /* LineSensor_hpp */
