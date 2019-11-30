#ifndef INTEGER_H
#define INTEGER_H

#include <string>
#include "element.h"
#include "null_iterator.h"

class Integer : public Element
{
  public:
    Integer(int i) : _integer(i)
    {
    }
    void add(Element *s)
    {
        throw(std::string("It's an integer!"));
    }
    int size()
    {
        return 1;
    }
    std::string toString()
    {
        return std::to_string(_integer);
    }
    Iterator *createIterator()
    {
        return new NullIterator;
    }
    void setOperator(char ope)
    {
        throw(std::string("Cannot set operator on it!"));
    }
    void accept(Visitor *fsv) 
    {
        fsv->visitInteger(this);
    }

  private:
    int _integer;
};

#endif