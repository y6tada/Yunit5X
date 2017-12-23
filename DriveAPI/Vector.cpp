#include "Vector.hpp"

vector_xy setVectorZero() {
    vector_xy rslt;
    rslt.x = 0;
    rslt.y = 0;
    rslt.r = 0;
    return rslt;
}

vector_xy makeXYFromRT(double radius, float theta) {
    
    vector_xy rslt;
    rslt.x = radius * sin(theta / -180.0 * M_PI);
    rslt.y = radius * cos(theta / -180.0 * M_PI);
    
    return rslt;
}

vector_xy makeXY(double x, double y) {
    
    vector_xy rslt;
    rslt.x = x;
    rslt.y = y;
    
    return rslt;
}
