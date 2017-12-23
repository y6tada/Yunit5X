#ifndef BoundCtrl_hpp
#define BoundCtrl_hpp

#include "mbed.h"
#include "Vector.hpp"
#include "SensorAPI.hpp"

class BoundCtrl {
    unsigned int LineAllCnt = 0;
    float margin            = 15.0;
    float keepOut           = 5.0;
    float odmetryRatio      = 0.8;
    float xMinDiameter      = 80;
    float xMinDifferential  = 40;
    float yMinDiameter      = 100;
    float yMinDifferential  = 50;
    float inLineArea_F;
    float inLineArea_B;
    float inLineArea_R;
    float inLineArea_L;
    
public:
    BoundCtrl();
    void set(vector_xy *move);
};

#endif /* BoundCtrl_hpp */
