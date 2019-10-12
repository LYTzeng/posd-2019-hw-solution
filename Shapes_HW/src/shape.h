#ifndef SHAPE
#define SHAPE
#include <math.h>

class Shape
{
public:
    // Virtual Methods
    virtual double area() const = 0;
    virtual double perimeter() const = 0;
    virtual double sumOfSquares() const = 0;
};
#endif