#ifndef SerialDebug_hpp
#define SerialDebug_hpp

#include "mbed.h"
#include "Yunit5X.h"
#include "SensorAPI.hpp"

class SerialDebug {
    mbed::RawSerial serial;
    mbed::Ticker    ticker;

    void callback();
    
public:
    SerialDebug();
    void startPrintDebug(int period);
    
    void printHoldSensor();
    void printBallSensor();
    void printLineSensor();
    void printSonicSensor();
    void printPixyRawData(int sign);
    void printPixyRT(int sign);
};

#endif /* SerialDebug_hpp */
