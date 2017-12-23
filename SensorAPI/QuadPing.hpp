#ifndef QuadPing_hpp
#define QuadPing_hpp

#include "mbed.h"
#include "Yunit5X.h"
#include "PAMovingAverage.h"

#define us_per_cm               59
#define numOfSonicMovingAverage 4

class QuadPing {
    
    mbed::DigitalInOut _dpF;
    mbed::DigitalInOut _dpB;
    mbed::DigitalInOut _dpR;
    mbed::DigitalInOut _dpL;
    
    mbed::InterruptIn _eventF;
    mbed::InterruptIn _eventB;
    mbed::InterruptIn _eventR;
    mbed::InterruptIn _eventL;
    
    
    mbed::Timer _timer;
    mbed::Ticker _ticker;
    
    uint16_t pulse_rise[4];
    uint16_t pulseWidth[4];
    void sendSonic();
    
    void startTimerF();
    void stopTimerF();
    void startTimerB();
    void stopTimerB();
    void startTimerR();
    void stopTimerR();
    void startTimerL();
    void stopTimerL();
    
    PAMovingAverage<uint16_t, numOfSonicMovingAverage> aveF;
    PAMovingAverage<uint16_t, numOfSonicMovingAverage> aveB;
    PAMovingAverage<uint16_t, numOfSonicMovingAverage> aveR;
    PAMovingAverage<uint16_t, numOfSonicMovingAverage> aveL;
    
public:
    QuadPing();
    
    int getF();
    int getB();
    int getR();
    int getL();
    
    int getXDifferential();
    int getYDifferential();
    int getXDiameter();
    int getYDiameter();
};

#endif /* QuadPing_hpp */
