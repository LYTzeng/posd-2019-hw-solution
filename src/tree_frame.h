#ifndef TREE_FRAME_H
#define TREE_FRAME_H

#include <wx/treectrl.h>

#include "node.h"
#include "file.h"
#include "folder.h"
#include "link.h"
#include "filesystem_builder.h"
#include "iterator.h"
#include "observer_tree.h"
#include "observer.h"
#include "subject.h"
#include "concrete_subject.h"
#include <string>
#include <stdio.h>

class TreeFrame : public wxFrame
{
public:
    TreeFrame(const wxChar *title, int xpos, int ypos, int width, int height, char* argv) : wxFrame((wxFrame *)NULL, -1, title, wxPoint(xpos, ypos), wxSize(width, height))
    {
        _tree = new wxTreeCtrl(this, wxID_ANY, wxPoint(0, 0), wxSize(100, 200), wxTR_DEFAULT_STYLE | wxTR_SINGLE);

        FileSystemBuilder *fb = FileSystemBuilder::instance();

        fb->build(argv);
        _subject = new ConcreteSubject(fb->getRoot());
        _observerFS = new ObserverTree(_subject, _tree);
    }

    wxTreeCtrl *_tree;

private:
    Observer *_observerFS;
    ConcreteSubject *_subject;
};

#endif
