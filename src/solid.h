#ifndef SOLID
#define SOLID

#include <string>

class Solid
{
  public:
    virtual double bottomArea() const = 0;
    virtual double volume() const = 0;
    virtual int numberOfChild() {};
};

#endif