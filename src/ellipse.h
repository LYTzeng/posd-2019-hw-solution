#include <math.h>
#include <algorithm>

class Ellipse: public Shape
{
    public:
        Ellipse(double semiMajorAxes, double semiMinorAxes): _semiMajorAxes(semiMajorAxes), _semiMinorAxes(semiMinorAxes)
        {
            if (_semiMajorAxes < _semiMinorAxes)
            {
                std::swap(_semiMajorAxes, _semiMinorAxes);
            }
        }
        double area() const 
        {
            return M_PI * _semiMajorAxes * _semiMinorAxes;
        }
        double perimeter() const 
        {
            return 2 * M_PI * _semiMinorAxes + 4 * (_semiMajorAxes - _semiMinorAxes);
        }

    private:
        double _semiMajorAxes, _semiMinorAxes;
};