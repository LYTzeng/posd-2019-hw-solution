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
        // struct stat _st;
        // lstat(path.c_str(), &_st);
        // if (_st.st_mode & S_IFMT != S_IFREG)
        //     throw(std::string("It is not File!"));
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
