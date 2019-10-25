#ifndef ITERATOR_H
#define ITERATOR_H


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