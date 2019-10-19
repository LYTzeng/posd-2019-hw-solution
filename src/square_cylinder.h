#ifndef SQUARE_CYL
#define SQUARE_CYL

#include <math.h>
#include "./solid.h"

class SquareCylinder : public Solid
{
  public:
    SquareCylinder(double edge, double height) : _edge(edge), _height(height)
    {
    }
    double bottomArea() const override{
        return pow(_edge, 2);
    };
    double volume() const override{
        return bottomArea() * _height;
    };

  private:
    double _edge, _height;
};

#endif