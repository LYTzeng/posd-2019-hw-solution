#ifndef ITERATOR
#define ITERATOR

class Node;
class Iterator
{
public:
    virtual void first() = 0;
    virtual Node *currentItem() = 0;
    virtual void next() = 0;
    virtual bool isDone() = 0;
    virtual int size() = 0;
};

#endif