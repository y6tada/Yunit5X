#include "ImuSensor.hpp"

ImuSensor::ImuSensor()
:serial(IMU_TX_PIN, IMU_RX_PIN)
,led(LED2_PIN)
{
    serial.baud(IMU_BAUD);
    serial.attach(mbed::callback(this, &ImuSensor::callback), mbed::RawSerial::RxIrq);
}

void ImuSensor::callback() {
    led = 1;
    int8_t reading = serial.getc();
    led = 0;
    
    deg        = reading;
    deg_dt     = deg - deg_last;
    deg_last   = reading;
}

float ImuSensor::getError() {
    return (float)(deg - system_set_ofset) / 127.0;
}

float ImuSensor::getError_dt() {
    return imu_sma.addValue(deg_dt) / 12.7;
}

void ImuSensor::setPD(float Kp, float Kd) {
    system_set_kp = Kp;
    system_set_kd = Kd;
}

float ImuSensor::getPD() {
    return system_set_kp * getError() + system_set_kd * getError_dt();
}

void ImuSensor::setOfset(int8_t ofset) {
    system_set_ofset = ofset;
}

float ImuSensor::getOfset() {
    return system_set_ofset;
}
