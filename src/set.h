#ifndef SET_H
#define SET_H

#include "element.h"

class Set : public Element
{
  public:
    class SetIterator : public Iterator
    {
      public:
        SetIterator(Set *s) {}
        void first() = 0;
        Element *currentItem() = 0;
        void next() = 0;
        bool isDone() = 0;
    };

  public:
    Set() {}
    void add(Element *s) = 0;
    int size() = 0;
    std::string toString() = 0;
    Iterator *createIterator() = 0;
    void setOperator(char ope) = 0;
    void accept(Visitor *fsv) = 0;
};

#endif