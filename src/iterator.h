#ifndef ITERATOR_H
#define ITERATOR_H

class Element;
class Iterator
{
  public:
    virtual void first() = 0;
    virtual Element *currentItem() = 0;
    virtual void next() = 0;
    virtual bool isDone() = 0;
};

#endif