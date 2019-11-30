#include "flattened_set_visitor.h"
#include "../src/integer.h"
#include "../src/set.h"

FlattenedSetVisitor::FlattenedSetVisitor()
{
    _findSet = new Set();
}

void FlattenedSetVisitor::visitInteger(Integer *i)
{
    _findResult = i;
    _findSet->add(i);
}

void FlattenedSetVisitor::visitSet(Set *s)
{
    Iterator *it = s->createIterator();
    it->first();
    for (int childNum = 0; childNum < it->size(); childNum++)
    {
        it->currentItem()->accept(this);
        it->next();
    }
    _findResult = _findSet;
}

Element *FlattenedSetVisitor::getResult()
{
    return _findResult;
}