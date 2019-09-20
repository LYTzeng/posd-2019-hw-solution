#ifndef SORT
#define SORT
#include <algorithm>
#include <vector>
#include <iterator>
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
        _quickSort(_shapes->begin(), _shapes->begin() + _shapes->size() - 1, comp);
    }

private:
    std::vector<Shape *> *_shapes;

    typedef std::vector<Shape *>::iterator Iterator;

    template <class Compare>
    Iterator _partition(Iterator left, Iterator right, Compare comp)
    {
        Iterator i = left - 1;
        Iterator j;
        for (j = left; j < right; j++)
        {
            if (comp(*j, *right))
            {
                i++;
                std::iter_swap(i, j);
            }
        }

        std::iter_swap(i + 1, right);
        return i + 1;
    }

    template <class Compare>
    void _quickSort(Iterator left, Iterator right, Compare comp)
    {
        if (left < right)
        {
            Iterator q = _partition(left, right, comp);
            _quickSort(left, q - 1, comp);
            _quickSort(q + 1, right, comp);
        }
    }
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
        else if (sortByWhat == "perimeter")
            return a->perimeter() < b->perimeter();
        else if (sortByWhat == "sumOfSquares")
            return a->sumOfSquares() < b->sumOfSquares();
        else
            throw "Wrong constructor parameter";
    }
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
        else if (sortByWhat == "perimeter")
            return a->perimeter() > b->perimeter();
        else if (sortByWhat == "sumOfSquares")
            return a->sumOfSquares() > b->sumOfSquares();
        else
            throw "Wrong constructor parameter";
    }
};

#endif