#ifndef UTILITIES_H
#define UTILITIES_H

#include "node.h"
#include "folder.h"

//pratice here
int infoByte(Node *node)
{
    int total = 0;
    Folder *folder = dynamic_cast<Folder *>(node); // down cast
    if (folder != nullptr)
    { //it's a folder
        Node::Iterator *it = folder->createIterator();
        for (it->first(); !it->isDone(); it->next())
        {
            total += it->currentItem()->size();
        }
    }
    else
    {
        total += node->size();
    }
    return total;
}

#endif
