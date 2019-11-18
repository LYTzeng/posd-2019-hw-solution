#ifndef FILE_H
#define FILE_H

#include <string>

#include "node.h"
#include "null_iterator.h"

class File : public Node
{
public:
    File(std::string path) : Node(path)
    {
        if (nodeType != "file")
            throw(std::string("It is not File!"));
    }

    Iterator *createIterator() override
    {
        return new NullIterator();
    }

    void accept(FindVisitor *fv) override
    {
        fv->visitFile(this);
    }

    void accept(UpdatePathVisitor *upv) override
    {
        upv->visitFile(this);
    }
};

#endif
