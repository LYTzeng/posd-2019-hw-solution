#ifndef VISITOR
#define VISITOR

class Folder;
class File;
class Link;
class Node;

class Visitor
{
public:
    virtual void visitFolder(Folder *folder) = 0;
    virtual void visitFile(File *file) = 0;
    virtual void visitLink(Link *link) = 0;
};

#endif