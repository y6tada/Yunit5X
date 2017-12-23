#ifndef MotorCtrlLAP_hpp
#define MotorCtrlLAP_hpp

#include "mbed.h"
#include "Yunit5X.h"

class Motor {
    
private:
    mbed::PwmOut M1D;
    mbed::PwmOut M2D;
    mbed::PwmOut M3D;
    mbed::PwmOut M4D;
    
    mbed::DigitalOut M1P;
    mbed::DigitalOut M2P;
    mbed::DigitalOut M3P;
    mbed::DigitalOut M4P;
    
public:
    
    Motor(unsigned int period_us);
    
    void all_enable();
    void all_disable();
    
    void setRF(float pwm);
    void setRB(float pwm);
    void setLF(float pwm);
    void setLB(float pwm);
};

#endif /* MotorCtrlLAP_hpp */
