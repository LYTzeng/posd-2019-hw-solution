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

    std::string findNode(std::string name)
    {
        //TODO:
        // implementation findNode
        // folder->findNode(name) that should find all nodes(include child nodes and all offspring) under it.
        // file->findNode(name) that should find itself.
        // if find two nodes or more than two nodes.
        // Result should be separated by '\n'.
    }

private:

};

#endif
