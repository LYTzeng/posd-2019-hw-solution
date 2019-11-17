#ifndef FIND_VISITOR_H
#define FIND_VISITOR_H
#include <string>
#include "visitor.h"

class FindVisitor : public Visitor
{
public:
    FindVisitor(std::string name); // Name is the target we want to find.
    void visitFolder(Folder *folder);
    void visitFile(File *file);
    void visitLink(Link *link); // You only need to check the link itself,and you don't have to check the node that the link point to!
    std::string findResult();
    std::string traverseSearch(Node *node, std::string name);
private:
    std::string _name;
    std::string _searchResult;
};

#endif