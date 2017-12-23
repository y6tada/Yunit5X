#ifndef Motion_hpp
#define Motion_hpp

class Motion;

#include "mbed.h"
#include "Vector.hpp"
#include "DriveAPI.hpp"
#include "SensorAPI.hpp"
#include "PAMovingAverage.h"

#define abs(x) ((x)>0?(x):-(x))

enum distance_type {
    distance_close,
    distance_middle,
    distance_long,
    front_of_goal,
};

class Motion {
    PAMovingAverage<float, 10> smaBallDeg;
    // variables
    float m_speed;
    int   m_ofset           = 0;
    float m_forwardRation   = 1.2;
    float m_holdCount       = 0;
    float m_holdCountLimit  = 5.0;
    // functions
    int  getBallTrackDegree(uint16_t back_limit);
    
public:
    Motion();
    void setSpeed(float speed);
    void setOfset(int8_t ofset);
    void ballTracking(vector_xy *move);
    void backOwnGoal(vector_xy *move, int x_margin, int y_margin);
    void wallBreak(vector_xy *move);
};

#endif /* Motion_hpp */
