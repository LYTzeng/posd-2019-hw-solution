#include "update_path_visitor.h"
#include "iterator.h"
#include "folder.h"
#include "file.h"
#include "link.h"

UpdatePathVisitor::UpdatePathVisitor()
{ /* Do Nothing */
}
void UpdatePathVisitor::visitFolder(Folder *folder)
{
    std::string newDir = folder->getPath();
    newDir.insert(newDir.end(), 1, '/');
    Iterator *it = folder->createIterator();
    it->first();
    for (int childNum = 0; childNum < it->size(); childNum++)
    {
        Node *currentNode = it->currentItem();
        currentNode->moveToNewPath(newDir);
        currentNode->accept(this);
        it->next();
    }
}
void UpdatePathVisitor::visitFile(File *file)
{ /* Do Nothing */
}
void UpdatePathVisitor::visitLink(Link *link)
{ /* Do Nothing */
}
