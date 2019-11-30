#ifndef FLATTENED
#define FLATTENED

#include <string>
#include "visitor.h"

class Element;
class Set;
class FlattenedSetVisitor : public Visitor
{
  public:
    FlattenedSetVisitor();
    void visitInteger(Integer *i);
    void visitSet(Set *s);
    Element *getResult();

  private:
    Element *_findResult;
    Set *_findSet;
};

#endif