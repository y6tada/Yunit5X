#include "PixyCAM.hpp"

PixyCAM:: PixyCAM()
:serial(PIXY_TX_PIN, PIXY_RX_PIN)
,led(LED1_PIN)
{
    serial.baud(PIXY_BAUD);
    serial.attach(mbed::callback(this, &PixyCAM::callback), mbed::RawSerial::RxIrq);
}

void PixyCAM::callback() {
    led = 1;
    byte = serial.getc();
    led = 0;
    
    word = byte << 8 | byte_last;
    byte_last = byte;
    
    if(word == sync) flip = true;
    if(flip) {
        update();
    }
    flip = !flip;
}

void PixyCAM::setCenter(int x_origin, int y_origin) {
    xOrigin = x_origin;
    yOrigin = y_origin;
}

int PixyCAM::getRadius(int sign) {
    double x = (X[sign] - xOrigin);
    double y = (Y[sign] - yOrigin);
    return (int)sqrt(x*x + y*y);
}

int PixyCAM::getDegree(int sign) {
    double x = (X[sign] - xOrigin);
    double y = (Y[sign] - yOrigin);
    double rslt = atan2(-x, y) / M_PI * 180.0;
    return (int)rslt;
}

void PixyCAM::clearDatas() {
    for (int i = 0; i < MAX_SINGATURE_NUMBER; i++) {
        X[i] = xOrigin;
        Y[i] = yOrigin;
        Width[i] = 0;
        Height[i] = 0;
    }
}

void PixyCAM::update() {
    if(gate_A == false) {
        count = 0;
        if(gate_B == false) {
            if(word == sync) {
                gate_B = true;
                clearDatas();
            }
            else {
                return;
            }
        }
        else {
            if(word == sync) {
                gate_A = true;
            }
            else {
                gate_B = false;
            }
        }
    }
    else {
        switch (count++) {
            case 0:
                checksum = word;
                break;
                
            case 1:
                signature = word;
                break;
                
            case 2:
                X[signature] = word;
                break;
                
            case 3:
                Y[signature] = word;
                break;
                
            case 4:
                Width[signature] = word;
                break;
                
            case 5:
                Height[signature] = word;
                gate_A = false;
                break;
                
            default:
                break;
        }
    }
}
