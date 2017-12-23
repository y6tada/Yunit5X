#include "mbed.h"
#include "SerialDebug.hpp"
#include "Loop.hpp"

Loop loop(2500);
SerialDebug debug;

int main() {
    
    imu.setPD(5.0, 2.0);
    camera.setCenter(160, 100);
    
    while(1) {
        debug.printPixyRT(1);
        wait_ms(50);
    }
    
    return 0;
}
