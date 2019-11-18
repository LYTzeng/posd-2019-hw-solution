#ifndef FILE_H
#define FILE_H

#include <string>
#include <sys/stat.h>
#include <sys/stat.h>

#include "node.h"
#include "null_iterator.h"

class File : public Node
{
public:
    File(std::string path) : Node(path)
    {
        struct stat st;
        stat(path.c_str(), &st);
        if (!S_ISREG(st.st_mode))
            throw(std::string("It is not File!"));
        else
            nodeType = "file";
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
