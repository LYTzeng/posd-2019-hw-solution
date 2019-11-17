#ifndef FILE_H
#define FILE_H

#include <string>
#include <sys/stat.h>

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

    NodeIterator *createIterator() override
    {
        return new NullIterator();
    }

    void accept(FindVisitor *fv) override
    {
        fv->visitFile(this);
    }
};

#endif
