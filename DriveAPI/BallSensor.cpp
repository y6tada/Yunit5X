#include "BallSensor.hpp"

BallSensor::BallSensor()
:serial(BALL_TX_PIN, BALL_RX_PIN)
,led(LED3_PIN)
,hold(HOLD_SENSOR_PIN)
{
    serial.baud(BALL_BAUD);
    serial.attach(mbed::callback(this, &BallSensor::callback), mbed::Serial::RxIrq);
}

void BallSensor::callback() {
    
    led = 1;
    uint8_t _data = serial.getc();
    led = 0;
    
    range = 0;
    dir = 0;
    
    range    = _data & 0x07;
    dir      = _data >> 3;
    
    if(dir > 8) {
        dir -= 17;
    }
}

int8_t BallSensor::getDir() {
    return dir;
}

int8_t BallSensor::getRange() {
    return range;
}

void BallSensor::holdSensorUpdate() {
    if (hold.read()) {
        hold_sma = sma.addValue(1.0);
    }
    else {
        hold_sma = sma.addValue(0.0);
    }
}

float BallSensor::getHold() {
    return hold_sma;
}
