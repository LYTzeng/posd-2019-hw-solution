#ifndef FILE_H
#define FILE_H

#include <string>
#include <sys/stat.h>

#include "node.h"

class File : public Node
{
public:
    File(std::string path) : Node(path)
    {
        if (nodeType != "file")
            throw(std::string("It is not File!"));
    }

private:

};

#endif
