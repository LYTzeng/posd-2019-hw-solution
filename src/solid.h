#ifndef SOLID
#define SOLID

class Solid
{
  public:
    virtual double bottomArea() const = 0;
    virtual double volume() const = 0;
};

#endif