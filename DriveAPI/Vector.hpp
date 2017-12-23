#ifndef Vector_hpp
#define Vector_hpp

#include "mbed.h"

typedef struct {
    double x;
    double y;
    double r;
} vector_xy;

extern vector_xy setVectorZero();
extern vector_xy makeXYFromRT(double radius, float theta);
extern vector_xy makeXY(double x, double y);

#endif /* Vector_hpp */
