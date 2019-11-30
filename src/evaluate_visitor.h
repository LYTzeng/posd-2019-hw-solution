#ifndef EVALUATE_VISITOR
#define EVALUATE_VISITOR

#include "visitor.h"

class EvaluateVisitor : public Visitor
{
  public:
    EvaluateVisitor();
    virtual void visitInteger(Integer *i);
    virtual void visitSet(Set *s);
    double getResult();

  private:
    double _value;
};

#endif