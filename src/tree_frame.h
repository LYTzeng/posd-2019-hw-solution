#ifndef TREE_FRAME_H
#define TREE_FRAME_H

#include <wx/treectrl.h>
#include <wx/textctrl.h>
#include <wx/button.h>

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
    TreeFrame(const wxChar *title, int xpos, int ypos, int width, int height, char *argv) : wxFrame((wxFrame *)NULL, -1, title, wxPoint(xpos, ypos), wxSize(width, height))
    {
        _tree = new wxTreeCtrl(this, wxID_ANY, wxPoint(0, 0), wxSize(200, 650), wxTR_DEFAULT_STYLE | wxTR_SINGLE);
        _text = new wxTextCtrl(this, wxID_ANY, _T("WelCome To POSD_EDITOR!"), wxPoint(200, 0), wxSize(800, 500), wxTE_MULTILINE);
        _button = new wxButton(this, wxID_ANY, _T("Save"), wxPoint(200, 500), wxSize(800, 100));

        FileSystemBuilder *fb = FileSystemBuilder::instance();

        fb->build(argv);
        _subject = new ConcreteSubject(fb->getRoot());
        _observerFS = new ObserverTree(_subject, _tree);
    }

    wxTreeCtrl *_tree;
    wxTextCtrl *_text;
    wxButton *_button;

private:
    Observer *_observerFS;
    ConcreteSubject *_subject;
};

#endif
