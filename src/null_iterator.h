#ifndef NULL_ITERATOR_H
#define NULL_ITERATOR_H

#include <string>
#include "iterator.h"

class NullIterator : public Iterator
{
  public:
    NullIterator() {} // Don't Throw exception
    void first() // Throw exception
    {
        throw(std::string("No child member!"));
    }
    Element *currentItem()// Throw exception
    {
        throw(std::string("No child member!"));
    }
    void next() // Throw exception
    {
        throw(std::string("No child member!"));
    }
    bool isDone() // Don't Throw exception
    {
        return true;
    }
    int size()
    {
        return 1;
    }
};

#endif