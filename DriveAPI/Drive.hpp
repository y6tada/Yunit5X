#ifndef Drive_hpp
#define Drive_hpp

#include "mbed.h"
#include "Yunit5X.h"
#include "Vector.hpp"
#include "SensorAPI.hpp"
#include "MotorCtrlLAP.hpp"

#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))

class Drive {
    mbed::PwmOut     esc;
    mbed::Timeout    kicker_R_disableTimeout;
    mbed::Timeout    kicker_L_disableTimeout;
    mbed::Timeout    kicker_R_readyTimeout;
    mbed::Timeout    kicker_L_readyTimeout;
    mbed::DigitalOut kicker_R;
    mbed::DigitalOut kicker_L;
    
    PAMovingAverage<float, 20> smaMoveX;
    PAMovingAverage<float, 20> smaMoveY;
    Motor motor;
    
    const float kick_nextReady_delay = 0.8;
    bool    kicker_R_isReady = true;
    bool    kicker_L_isReady = true;
    
    void    kicker_R_Flip(void)  {kicker_R = 0;}
    void    kicker_R_Ready(void) {kicker_R_isReady = true;}
    void    kicker_L_Flip(void)  {kicker_L = 0;}
    void    kicker_L_Ready(void) {kicker_L_isReady = true;}
    
    float   deg2rad(int deg1, int deg2);
    float   _x, _y;
	
public:
	Drive();
    void RunDribbler(int pwr_0_to_1000);
    void enableAutoDrible(int dir, int range);
    void disableAutoDrible(void);
    
	void kick_R(void);
    void kick_L(void);
    
    void enable_all_motors(void);
    void disable_all_motors(void);
    
	void movePolar(float pwr, int degree, float turn);
	void moveComp(float VecX, float VecY, float turn);
    void moveVector(vector_xy *move);
    void getLatestVecXY(float *x, float *y);
};

#endif /* Drive_hpp */
