#ifndef COMPLEX_SOLID
#define COMPLEX_SOLID

#include <vector>
#include <iterator>
#include <string>
#include "solid.h"

using solidPtrIterator = std::vector<Solid *>::iterator;

class ComplexSolids : public Solid
{
  public:
    ComplexSolids(std::vector<Solid *> *solids) : _solids(solids)
    {
    }
    void add(Solid *s)
    {
        _solids->push_back(s);
    }
    double bottomArea() const override
    {
        double sum = 0;
        for (solidPtrIterator it = _solids->begin(); it != _solids->end(); it++)
        {
            sum += (*it)->bottomArea();
        }
        return sum;
    }
    double volume() const override
    {
        double sum = 0;
        for (solidPtrIterator it = _solids->begin(); it != _solids->end(); it++)
        {
            sum += (*it)->volume();
        }
        return sum;
    }
    int numberOfChild() override
    {
        return _solids->size();
    }

  private:
    std::vector<Solid *> *_solids;
};

#endif