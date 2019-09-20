#ifndef SORT
#define SORT
#include <algorithm>
#include <vector>
#include <string>
#include "./shape.h"

class Sort
{
public:
    Sort(std::vector<Shape *> *shapes) : _shapes(shapes) {}

    template <class Compare>
    void sortArea(Compare comp)
    {
        std::sort(_shapes->begin(), _shapes->end(), comp);
    }

    template <class Compare>
    void sortPerimeter(Compare comp)
    {
        std::sort(_shapes->begin(), _shapes->end(), comp);
    }

    template <class Compare>
    void sortSumOfSquares(Compare comp) 
    {
        std::sort(_shapes->begin(), _shapes->end(), comp);
    }

    template <class Compare>
    void quickSort(Compare comp)
    {
        //TODO:
    }
    // quickSort() function should be function template
    // You should write the quickSort by yourself!
    // In the loop of the quickSort algorithm, use Iterator to control your vector rather than index.
    // * **Example : for (std::vector<...>::iterator it...) * **

private:
    std::vector<Shape *> *_shapes;
};

// implement following call back function

bool areaAscendingComparison(Shape *a, Shape *b)
{
    return a->area() < b->area();
};

bool areaDescendingComparison(Shape *a, Shape *b)
{
    return a->area() > b->area();
};

// implement classes

class AscendingComparison
{
public:
    AscendingComparison(std::string sortByWhat) : sortByWhat(std::move(sortByWhat)) {}
    std::string sortByWhat;
    bool operator()(Shape *a, Shape *b)
    {
        if (sortByWhat == "area")
            return a->area() < b->area();
        else if(sortByWhat == "perimeter")
            return a->perimeter() < b->perimeter();
        else if(sortByWhat == "sumOfSquares")
            return a->sumOfSquares() < b->sumOfSquares();
        else throw "Wrong constructor parameter";
    }
private:
};

class DescendingComparison
{
public:
    DescendingComparison(std::string sortByWhat) : sortByWhat(std::move(sortByWhat)) {}
    std::string sortByWhat;
    bool operator()(Shape *a, Shape *b)
    {
        if (sortByWhat == "area")
            return a->area() > b->area();
        else if(sortByWhat == "perimeter")
            return a->perimeter() > b->perimeter();
        else if(sortByWhat == "sumOfSquares")
            return a->sumOfSquares() > b->sumOfSquares();
        else throw "Wrong constructor parameter";
    }
private:
};

#endif