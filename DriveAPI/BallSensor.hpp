#ifndef BallSensor_hpp
#define BallSensor_hpp

#include "mbed.h"
#include "Yunit5X.h"
#include "PAMovingAverage.h"

class BallSensor {
    mbed::RawSerial     serial;
    mbed::DigitalOut    led;
    mbed::DigitalIn     hold;
    PAMovingAverage<float, 25> sma;
    
    int8_t dir;
    int8_t range;
    float  hold_sma;
    void callback();

public:
    BallSensor();
    int8_t getDir();
    int8_t getRange();
    void   holdSensorUpdate();
    float  getHold();
};

#endif /* BallSensor_hpp */
