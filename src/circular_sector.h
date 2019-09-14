#include <math.h>

class CircularSector: public Shape
{
    public:
        CircularSector(double radius, double degree): _radius(radius), _degree(degree){}
        double area() const
        {
            return M_PI * pow(_radius, 2) * (_degree/360);
        }
        double perimeter() const
        {
            return 2 * M_PI * _radius * (_degree/360);
        }

    private:
        double _radius, _degree;
};
