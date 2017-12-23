#ifndef SensorAPI_hpp
#define SensorAPI_hpp

#include "PowerControl.hpp"
#include "BallSensor.hpp"
#include "ImuSensor.hpp"
#include "LineSensor.hpp"
#include "PixyCAM.hpp"
#include "QuadPing.hpp"

extern PowerControl powor;
extern BallSensor   ball;
extern ImuSensor    imu;
extern LineSensor   line;
extern PixyCAM      camera;
extern QuadPing     quadping;

#endif /* SensorAPI_hpp */
