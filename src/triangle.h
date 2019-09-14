#ifndef TRIANGLE
#define TRIANGLE
#include <math.h>
#include <string>
#include <stdexcept>
#include "shape.h"

class Triangle: public Shape
{
    public:
        Triangle(double x1, double y1, double x2, double y2, double x3, double y3):_x1(x1), _x2(x2), _x3(x3), _y1(y1), _y2(y2), _y3(y3)
        {
            _side1 = sqrt(pow(_x1 - _x2,2) + pow(_y1 - _y2,2));
            _side2 = sqrt(pow(_x2 - _x3,2) + pow(_y2 - _y3,2));
            _side3 = sqrt(pow(_x1 - _x3,2) + pow(_y1 - _y3,2));

            if (!isIsoscelesTriangle())
                throw std::string("Not a IsoscelesTriangle.");
        }
        double area() const 
        {
            // Heron's
            double s = (_side1 + _side2 + _side3)/2;
            return sqrt(s * (s-_side1) *(s-_side2) *(s-_side3));
        }
        double perimeter() const 
        {
            return _side1 + _side2 + _side3;
        }
        bool isIsoscelesTriangle()
        {
            if (_side1 == _side2 || _side2 == _side3 || _side3 == _side1)
            {
                return true;
            }
            else return false;
        }

    private:
        double _x1 , _x2, _x3, _y1, _y2 , _y3;
        double _side1, _side2, _side3;
};
#endif