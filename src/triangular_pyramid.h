#ifndef TRIANGULAR_PYR
#define TRIANGULAR_PYR

#include <math.h>
#include "solid.h"

class TriangularPyramid : public Solid
{
  public:
    TriangularPyramid(double x1, double y1, double x2, double y2, double x3, double y3, double height) : _x1(x1), _x2(x2), _x3(x3), _y1(y1), _y2(y2), _y3(y3), _height(height)
    {
        _a = _edge(x1, y1, x2, y2);
        _b = _edge(x1, y1, x3, y3);
        _c = _edge(x2, y2, x3, y3);
        if (_a + _b <= _c || _c + _b <= _a || _a + _c <= _b)
            throw(std::string("Bottom is not a Triangle!"));
        _s = (_a + _b + _c) / 2.0;
    }
    double bottomArea() const override
    {
        return sqrt(_s * (_s - _a) * (_s - _b) * (_s - _c));
    }
    double volume() const override
    {
        return bottomArea() * _height * (1.0 / 3.0);
    }

  private:
    double _x1, _x2, _x3, _y1, _y2, _y3, _height;
    double _a, _b, _c, _s;
    double _edge(double xa, double ya, double xb, double yb)
    {
        return sqrt(pow((xb - xa), 2) + pow((yb - ya), 2));
    }
};

#endif
