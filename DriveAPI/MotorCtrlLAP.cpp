#include "MotorCtrlLAP.hpp"

Motor::Motor(unsigned int lap_control_period_us)
:M1D(M1D_PIN), M2D(M2D_PIN), M3D(M3D_PIN), M4D(M4D_PIN)
,M1P(M1P_PIN), M2P(M2P_PIN), M3P(M3P_PIN), M4P(M4P_PIN)
{
    M1D.period_us(lap_control_period_us);
    M2D.period_us(lap_control_period_us);
    M3D.period_us(lap_control_period_us);
    M4D.period_us(lap_control_period_us);
}

/* ========== Motors enable/disable control function ========== */
void Motor::all_enable() {
    M1P = 1;
    M2P = 1;
    M3P = 1;
    M4P = 1;
}

void Motor::all_disable() {
    M1P = 0;
    M2P = 0;
    M3P = 0;
    M4P = 0;
}

/* ========== LAP Mode motor speed control ========== */
void Motor::setRF(float speed) {
    if(speed >  1.0) speed =  1.0;
    if(speed < -1.0) speed = -1.0;
    M1D = 0.5 + (speed / 2.0);
}

void Motor::setRB(float speed) {
    if(speed >  1.0) speed =  1.0;
    if(speed < -1.0) speed = -1.0;
    M2D = 0.5 - (speed / 2.0);
}

void Motor::setLB(float speed) {
    if(speed >  1.0) speed =  1.0;
    if(speed < -1.0) speed = -1.0;
    M3D = 0.5 + (speed / 2.0);
}

void Motor::setLF(float speed) {
    if(speed >  1.0) speed =  1.0;
    if(speed < -1.0) speed = -1.0;
    M4D = 0.5 + (speed / 2.0);
}
