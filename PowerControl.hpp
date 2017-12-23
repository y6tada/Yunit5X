#ifndef PowerControl_hpp
#define PowerControl_hpp

#include "mbed.h"
#include "Yunit5X.h"
#include "PAMovingAverage.h"

class PowerControl {
    mbed::AnalogIn  battref;
    PAMovingAverage<float, 100> smaPowerControl;
    float underVoltageLimit = 16.0;
    
public:
    PowerControl();
    void  setUnderVoltageLimit(float target_voltage);
    float getNowVoltage();
    float getLimitVoltage();
    float getPowerRatio();
    float getSpeedRatioFromBattery(float target_voltage);
};

#endif /* PowerControl_hpp */
