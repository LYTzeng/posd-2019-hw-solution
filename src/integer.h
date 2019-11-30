#ifndef INTEGER_H
#define INTEGER_H

#include "element.h"

class Integer : public Element
{
  public:
    Integer(int i) : _integer(i)
    {

    }
    void add(Element *s) = 0;
    int size() = 0;
    std::string toString() = 0;
    Iterator *createIterator() = 0;
    void setOperator(char ope) = 0;
    void accept(Visitor *fsv) = 0;

  private:
    int _integer;
};

#endif