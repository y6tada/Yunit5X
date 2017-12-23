#include "SerialDebug.hpp"

SerialDebug::SerialDebug()
:serial(USBTX, USBRX)
{
    serial.baud(PC_BAUD);
}

void SerialDebug::callback() {
//    printBallSensor();
//    printHoldSensor();
//    printOmniCamera(0);
}

void SerialDebug::startPrintDebug(int period) {
    ticker.attach(mbed::callback(this, &SerialDebug::callback), period);
}

void SerialDebug::printHoldSensor() {
    serial.printf("Hold:%.2f\n", ball.getHold());
}

void SerialDebug::printSonicSensor() {
    serial.printf("XD:%5d YD:%5d XT:%5d YT:%5d\n"
                  ,quadping.getXDifferential()
                  ,quadping.getYDifferential()
                  ,quadping.getXDiameter()
                  ,quadping.getYDiameter()
                  );
}

void SerialDebug::printLineSensor() {
    serial.printf("LINE:%2d %2d %2d %2d %2d %2d %2d %2d %2d %2d %2d %2d \n"
                  ,line.FL
                  ,line.FC
                  ,line.FR
                  
                  ,line.RF
                  ,line.RC
                  ,line.RB
                  
                  ,line.BR
                  ,line.BC
                  ,line.BL
                  
                  ,line.LB
                  ,line.LC
                  ,line.LF
                  );
}

void SerialDebug::printBallSensor() {
    serial.printf("dir:%3d\trng:%3d\n"
                  ,ball.getDir()
                  ,ball.getRange()
                  );
}

void SerialDebug::printPixyRawData(int sign) {
    serial.printf("C:%4d\t", camera.checksum);
    serial.printf("X:%4d\t", camera.X[sign]);
    serial.printf("Y:%4d\t", camera.Y[sign]);
    serial.printf("W:%4d\t", camera.Width[sign]);
    serial.printf("H:%4d\t", camera.Height[sign]);
    serial.printf("\n");
}

void SerialDebug::printPixyRT(int sign) {
    serial.printf("R:%3d\tT:%3d\n", camera.getRadius(sign), camera.getDegree(sign));
}

