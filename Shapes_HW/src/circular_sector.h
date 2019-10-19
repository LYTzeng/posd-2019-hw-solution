#ifndef CIRCULAR_SEC
#define CIRCULAR_SEC
#include <math.h>
#include <stdio.h>
#include "shape.h"

class CircularSector : public Shape
{
public:
    CircularSector(double radius, double degree) : _radius(radius), _degree(degree) {}
    double area() const
    {
        return M_PI * pow(_radius, 2) * (_degree / 360);
    }
    double perimeter() const
    {
        return 2 * M_PI * _radius * (_degree / 360) + 2 * _radius;
    }
    double sumOfSquares() const
    {
        double area = this->area();
        double perimeter = this->perimeter();
        return pow(area, 2) + pow(perimeter, 2);
    }

private:
    double _radius, _degree;
};
#endif