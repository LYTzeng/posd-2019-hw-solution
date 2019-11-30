#include <string>

#include "evaluate_visitor.h"
#include "flattened_set_visitor.h"
#include "../src/integer.h"
#include "../src/set.h"

EvaluateVisitor::EvaluateVisitor()
{
    _value = 0;
}

void EvaluateVisitor::visitInteger(Integer *i)
{
    _value = std::stod(i->toString());
}

void EvaluateVisitor::visitSet(Set *s)
{
    Iterator *it = s->createIterator();
    it->first();

    if (s->getOpe() == '+')
    {
        double thisSum = 0;
        for (int childNum = 0; childNum < it->size(); childNum++)
        {
            EvaluateVisitor *childEV = new EvaluateVisitor();
            it->currentItem()->accept(childEV);
            thisSum += childEV->getResult();
            it->next();
        }
        _value = thisSum;
    }
    if (s->getOpe() == '-')
    {
        // first element
        EvaluateVisitor *childEV = new EvaluateVisitor();
        it->currentItem()->accept(childEV);
        double thisSubtract = childEV->getResult();
        it->next();
        delete childEV;

        for (int childNum = 1; childNum < it->size(); childNum++)
        {
            EvaluateVisitor *childEV = new EvaluateVisitor();
            it->currentItem()->accept(childEV);
            thisSubtract -= childEV->getResult();
            it->next();
        }

        _value = thisSubtract;
    }
    if (s->getOpe() == '*')
    {
        double thisMult = 1;
        for (int childNum = 0; childNum < it->size(); childNum++)
        {
            EvaluateVisitor *childEV = new EvaluateVisitor();
            it->currentItem()->accept(childEV);
            thisMult *= childEV->getResult();
            it->next();
        }
        _value = thisMult;
    }
    if (s->getOpe() == '/')
    {
        // first element
        EvaluateVisitor *childEV = new EvaluateVisitor();
        it->currentItem()->accept(childEV);
        double thisElement = childEV->getResult();
        it->next();
        delete childEV;

        for (int childNum = 1; childNum < it->size(); childNum++)
        {
            EvaluateVisitor *childEV = new EvaluateVisitor();
            it->currentItem()->accept(childEV);
            double childResult = childEV->getResult();
            if (childResult == 0.0)
                throw(std::string("Divide by zero!"));
            thisElement = thisElement / childResult;
            it->next();
        }
        _value = thisElement;
    }
}

double EvaluateVisitor::getResult()
{
    double ans = _value;
    _value = 0;
    return ans;
}