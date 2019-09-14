#ifndef TRIANGLE
#define TRIANGLE
#include <math.h>
#include <string>

class Triangle: public Shape
{
    public:
        Triangle(double (&point1)[2], double (&point2)[2], double (&point3)[2]): _point1(point1), _point2(point2), _point3(point3)
        {
            _side1 = sqrt(pow(_point1[0] - _point2[0],2) + pow(_point1[1] - _point2[1],2));
            _side2 = sqrt(pow(_point2[0] - _point3[0],2) + pow(_point2[1] - _point3[1],2));
            _side3 = sqrt(pow(_point3[0] - _point1[0],2) + pow(_point3[1] - _point1[1],2));

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
        double (&_point1)[2], (&_point2)[2], (&_point3)[2];
        double _side1, _side2, _side3;
};
#endif