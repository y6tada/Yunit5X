#include "Loop.hpp"

Loop::Loop(uint16_t loop_period_us)
:ticker()
,sw_left(SW_LEFT_PIN)
,sw_right(SW_RIGHT_PIN)
{
    ticker.attach_us(mbed::callback(this, &Loop::callback), loop_period_us);
}

void Loop::callback() {
    switch (getSwStatus()) {
        case sw_both_down:
            drive.disable_all_motors();
            drive.RunDribbler(0);
            break;
            
        case sw_right_up:
            drive.disable_all_motors();
            break;
            
        case sw_left_up:
            drive.enable_all_motors();
            move.r = imu.getPD();
            motion.ballTracking(&move);
            motion.wallBreak(&move);
            bound.set(&move);
            break;
            
        case sw_both_up:
            drive.disable_all_motors();
            move = setVectorZero();
            drive.kick_R();
            drive.kick_L();
            break;
            
        default:
            break;
    }
    
    ball.holdSensorUpdate();
    drive.moveVector(&move);
}

