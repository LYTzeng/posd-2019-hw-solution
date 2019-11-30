#ifndef VISITOR_H
#define VISITOR_H

class Set;
class Visitor
{
  public:
    virtual void visitInteger(Integer *i) = 0;
    virtual void visitSet(Set *s) = 0;
};

#endif