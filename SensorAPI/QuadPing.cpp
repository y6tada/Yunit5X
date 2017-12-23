#include "QuadPing.hpp"

QuadPing::QuadPing()
:_dpF(USD_F_PIN)     ,_dpB(USD_B_PIN)     ,_dpR(USD_R_PIN)     ,_dpL(USD_L_PIN)
,_eventF(USD_F_PIN)  ,_eventB(USD_B_PIN)  ,_eventR(USD_R_PIN)  ,_eventL(USD_L_PIN)
,_timer()
,_ticker()
{
    _eventF.rise(mbed::callback(this, &QuadPing::startTimerF));
    _eventF.fall(mbed::callback(this, &QuadPing::stopTimerF));
    
    _eventB.rise(mbed::callback(this, &QuadPing::startTimerB));
    _eventB.fall(mbed::callback(this, &QuadPing::stopTimerB));
    
    _eventR.rise(mbed::callback(this, &QuadPing::startTimerR));
    _eventR.fall(mbed::callback(this, &QuadPing::stopTimerR));
    
    _eventL.rise(mbed::callback(this, &QuadPing::startTimerL));
    _eventL.fall(mbed::callback(this, &QuadPing::stopTimerL));
    
    _ticker.attach_us(mbed::callback(this, &QuadPing::sendSonic), SEND_SONIC_PERIOD);
    _timer.start();
}

void QuadPing::sendSonic() {
    _timer.reset();
    
    _dpF.output(); _dpB.output(); _dpR.output(); _dpL.output();
    _dpF.write(0); _dpB.write(0); _dpR.write(0); _dpL.write(0);
    wait_us(3);
    _dpF.write(1); _dpB.write(1); _dpR.write(1); _dpL.write(1);
    wait_us(3);
    _dpF.write(0); _dpB.write(0); _dpR.write(0); _dpL.write(0);
    _dpF.input();  _dpB.input();  _dpR.input();  _dpL.input();
}

int QuadPing::getF() {
    return aveF.addValue(pulseWidth[0] / us_per_cm);
}

int QuadPing::getB() {
    return aveB.addValue(pulseWidth[1] / us_per_cm);
}

int QuadPing::getR() {
    return aveR.addValue(pulseWidth[2] / us_per_cm);
}

int QuadPing::getL() {
    return aveL.addValue(pulseWidth[3] / us_per_cm);
}

int QuadPing::getXDifferential() {
    return getR() - getL();
}

int QuadPing::getYDifferential() {
    return getB() - getF();
}

int QuadPing::getXDiameter() {
    return getR() + getL();
}

int QuadPing::getYDiameter() {
    return getF() + getB();
}
/* ====================================================================== */

void QuadPing::startTimerF() {
    pulse_rise[0] = _timer.read_us();
}
void QuadPing::stopTimerF() {
    pulseWidth[0] = _timer.read_us() - pulse_rise[0];
}

void QuadPing::startTimerB() {
    pulse_rise[1] = _timer.read_us();
}
void QuadPing::stopTimerB() {
    pulseWidth[1] = _timer.read_us() - pulse_rise[1];
}


void QuadPing::startTimerR() {
    pulse_rise[2] = _timer.read_us();
}
void QuadPing::stopTimerR() {
    pulseWidth[2] = _timer.read_us() - pulse_rise[2];
}


void QuadPing::startTimerL() {
    pulse_rise[3] = _timer.read_us();
}
void QuadPing::stopTimerL() {
    pulseWidth[3] = _timer.read_us() - pulse_rise[3];
}
