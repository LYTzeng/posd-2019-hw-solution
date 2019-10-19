#ifndef CONE
#define CONE

#include <math.h>
#include "./solid.h"

class Cone : public Solid
{
  public:
    Cone(double x1, double y1, double x2, double y2, double height) : _x1(x1), _x2(x2), _y1(y1), _y2(y2), _height(height)
    {
        _radius = sqrt(pow((_x2 - _x1), 2) + pow((_y2 - _y1), 2));
        if (_radius == 0)
            throw std::string("Bottom is not a Circle!");
    }
    double bottomArea() const override
    {
        return M_PI * pow(_radius, 2);
    }
    double volume() const override
    {
        return bottomArea() * _height * (1.0 / 3.0);
    }

  private:
    double _x1, _x2, _y1, _y2, _height;
    double _radius;
};

#endif