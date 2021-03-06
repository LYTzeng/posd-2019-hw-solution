#ifndef NULL_ITERATOR
#define NULL_ITERATOR

#include <string>

#include "iterator.h"

class NullIterator : public Iterator
{
public:
    void first() override
    {
        throw std::string("no child member");
    }
    Node *currentItem() override
    {
        throw std::string("no child member");
    }
    void next() override
    {
        throw std::string("no child member");
    }
    bool isDone() override
    {
        return true;
    }
    int size() override
    {
        throw std::string("no child member");
    }
};

#endif