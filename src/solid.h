#ifndef SOLID
#define SOLID

#include <string>
#include <vector>

class Solid
{
  public:
    virtual double bottomArea() const = 0;
    virtual double volume() const = 0;
    virtual int numberOfChild() {};
    virtual void add() {};
    virtual std::vector<Solid *> find(double volumeMin, double volumeMax, double bottomAreaMin, double bottomAreaMax)
    {
        std::vector<Solid *> leafItself;
        if (volume() >= volumeMin && volume() <= volumeMax
        && bottomArea() >= bottomAreaMin && bottomArea() <= bottomAreaMax)
        {
            leafItself.push_back(this);
        }
        return leafItself;
    }
};

#endif