#ifndef IMU_hpp
#define IMU_hpp

#include "mbed.h"
#include "Yunit5X.h"
#include "PAMovingAverage.h"

class ImuSensor {
    mbed::RawSerial  serial;
    mbed::DigitalOut led;
    PAMovingAverage<float, IMU_NUM_OF_SMA> imu_sma;
    
    float system_set_kp = 0;
    float system_set_kd = 0;
    float deg_dt;
    int deg, deg_last;
    int system_set_ofset = 0;
    
    void callback();
    
public:
    ImuSensor();
    float  getError();
    float  getError_dt();
    void   setPD(float Kp, float Kd);
    float  getPD();
    void   setOfset(int8_t ofset);
    float  getOfset();
};

#endif /* IMU_hpp */
