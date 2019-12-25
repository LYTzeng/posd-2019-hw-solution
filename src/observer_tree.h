#ifndef OBSERVER_FS
#define OBSERVER_FS
// Concrete Observer
#include "wx/wx.h"
#include <wx/treectrl.h>
#include <wx/event.h>
#include <string>

#include "node.h"
#include "file.h"
#include "folder.h"
#include "link.h"
#include "filesystem_builder.h"
#include "iterator.h"
#include "concrete_subject.h"

class ObserverTree : public Observer
{
public:
    ObserverTree(ConcreteSubject *s, wxTreeCtrl *tree) : _subject(s), _tree(tree)
    {
        _subject->attach(this);
        _root = _subject->getRootState();
        wxTreeItemId rootId = _tree->AddRoot(std::string(_root->name() + ", " + std::to_string(_root->size())).c_str());
        growTree(rootId, _root);
        _tree->ExpandAllChildren(rootId);
    }

    void growTree(wxTreeItemId rootId, Node *rootNode)
    {
        Iterator *it = rootNode->createIterator();
        for (it->first(); !it->isDone(); it->next())
        {
            Node *currentNode = it->currentItem();
            if (currentNode->nodeType == "file" || currentNode->nodeType == "symlink")
            {
                wxTreeItemId leafId = _tree->AppendItem(rootId, std::string(currentNode->name() + ", " + std::to_string(currentNode->size())).c_str()); // leaf node
            }
            else if (currentNode->nodeType == "folder")
            {
                wxTreeItemId internalNodeId = _tree->AppendItem(rootId, std::string(currentNode->name() + ", " + std::to_string(currentNode->size())).c_str()); // internal node
                growTree(internalNodeId, it->currentItem());
            }
        }
    }

    void update()
    {
    }

private:
    ConcreteSubject *_subject;
    wxTreeCtrl *_tree;
    Node *_root;
};

#endif