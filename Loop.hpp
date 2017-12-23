#ifndef Loop_hpp
#define Loop_hpp

#include "mbed.h"
#include "Yunit5X.h"
#include "DriveAPI.hpp"
#include "SensorAPI.hpp"

enum sw_status {
    sw_error     = -1,
    sw_both_down = 0,
    sw_left_up   = 1,
    sw_right_up  = 2,
    sw_both_up   = 3
};

class Loop {
    mbed::Ticker    ticker;
    mbed::DigitalIn sw_left;
    mbed::DigitalIn sw_right;
    
    vector_xy move;
    
    sw_status getSwStatus() {
        if( sw_left &&  sw_right) return sw_both_down;
        if( sw_left && !sw_right) return sw_right_up;
        if(!sw_left &&  sw_right) return sw_left_up;
        if(!sw_left && !sw_right) return sw_both_down;
        return sw_error;
    }
    
public:
    Loop(uint16_t loop_period_us);
    void callback();
};

#endif /* Loop_hpp */
