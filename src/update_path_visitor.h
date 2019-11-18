#ifndef UPDATE_PATH_VISITOR
#define UPDATE_PATH_VISITOR

#include "visitor.h"

class UpdatePathVisitor : public Visitor
{
public:
    UpdatePathVisitor();
    ~UpdatePathVisitor();
    void visitFolder(Folder *folder);
    void visitFile(File *file);
    void visitLink(Link *link);
};

#endif