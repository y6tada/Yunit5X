#include "LineSensor.hpp"

LineSensor::LineSensor():serial(TEENSY_TX_PIN, TEENSY_RX_PIN) {
    serial.baud(TEENSY_BAUD);
}

void LineSensor::init(uint8_t dataNum, uint8_t FirstSync, uint8_t LastSync) {
    dataNum    = dataNum;
    FirstSync  = FirstSync;
    LastSync   = LastSync;
}

void LineSensor::update(uint8_t reading) {
    if(cash_data_last == FirstSync && reading == LastSync) {
        count = 0;
    }
    else if(count < dataNum) {
        cash[count] = reading;
        if (count == 1) {
            updateSensorStatus(cash[0], cash[1]);
        }
        count ++;
    }
    
    cash_data_last = reading;
}

void LineSensor::updateSensorStatus(uint8_t HighByte, uint8_t LowByte) {
    FL = bitRead(HighByte, 0);
    FC = bitRead(HighByte, 1);
    FR = bitRead(HighByte, 2);
    
    RF = bitRead(HighByte, 3);
    RC = bitRead(HighByte, 4);
    RB = bitRead(HighByte, 5);
    
    BR = bitRead(HighByte, 6);
    BC = bitRead(HighByte, 7);
    BL = bitRead(LowByte, 0);
    
    LB = bitRead(LowByte, 1);
    LC = bitRead(LowByte, 2);
    LF = bitRead(LowByte, 3);
    
    OR = HighByte | LowByte;
}
