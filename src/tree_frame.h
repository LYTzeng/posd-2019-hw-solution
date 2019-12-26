#ifndef TREE_FRAME_H
#define TREE_FRAME_H

#include <wx/treectrl.h>
#include <wx/textctrl.h>
#include <wx/button.h>
#include <wx/event.h>

#include "node.h"
#include "file.h"
#include "folder.h"
#include "link.h"
#include "filesystem_builder.h"
#include "iterator.h"
#include "observer_tree.h"
#include "observer_editor.h"
#include "observer.h"
#include "subject.h"
#include "concrete_subject.h"
#include <string>
#include <iostream>
#include <regex>

class TreeFrame : public wxFrame
{
public:
    TreeFrame(const wxChar *title, int xpos, int ypos, int width, int height, char *argv) : wxFrame((wxFrame *)NULL, -1, title, wxPoint(xpos, ypos), wxSize(width, height))
    {
        // Components
        _tree = new wxTreeCtrl(this, wxID_ANY, wxPoint(0, 0), wxSize(200, 650), wxTR_DEFAULT_STYLE | wxTR_SINGLE);
        _text = new wxTextCtrl(this, wxID_ANY, _T("Welcome To POSD_EDITOR!"), wxPoint(200, 0), wxSize(800, 500), wxTE_MULTILINE);
        _text->Enable(false);
        _button = new wxButton(this, wxID_ANY, _T("Save"), wxPoint(200, 500), wxSize(800, 100));
        _button->Enable(false);

        // Event Binding
        _tree->Bind(wxEVT_LEFT_DOWN, &TreeFrame::_onTreeClick, this);
        _tree->Bind(wxEVT_LEFT_DCLICK, &TreeFrame::_onTreeDoubleClick, this);
        _button->Bind(wxEVT_LEFT_DOWN, &TreeFrame::_onButtonClick, this);
        _text->Bind(wxEVT_KEY_DOWN, &TreeFrame::_onKeyDownSave, this);

        // Tree View Initialize
        FileSystemBuilder *fb = FileSystemBuilder::instance();
        fb->build(argv);
        _subject = new ConcreteSubject(fb->getRoot());
        _observerTree = new ObserverTree(_subject, _tree);
        _observerEditor = new ObserverEditor(_subject, _text, _button); // Editor Observer
    }

    wxTreeCtrl *_tree;
    wxTextCtrl *_text;
    wxButton *_button;

protected:
    DECLARE_EVENT_TABLE();

private:
    ObserverTree *_observerTree;
    ObserverEditor *_observerEditor;
    ConcreteSubject *_subject;
    // Key code
    int _keyCode;

    // Events
    void _onTreeClick(wxMouseEvent &event)
    {
        if (!event.LeftDown())
        {
            event.Skip();
            return;
        }
        wxTreeItemId hitId = _getwxTreeItemId(event);
        if (hitId)
        {
            _tree->ToggleItemSelection(hitId); // Highlight the node selected.
            _observerEditor->setValue(hitId);  // Set the value of the text box.
        }
    }

    void _onTreeDoubleClick(wxMouseEvent &event)
    {
        if (!event.LeftDClick())
        {
            event.Skip();
            return;
        }
        wxTreeItemId hitId = _getwxTreeItemId(event);
        if (hitId)
        {
            _tree->EditLabel(hitId); // Double click to edit the node's name.
        }
    }

    void _onButtonClick(wxMouseEvent &event)
    {
        if (_showMessageBox(std::string("You want save?")))
        {
            _subject->setTreeNodeContentById(_tree->GetFocusedItem(), _wxStringToStdString(_text->GetValue()));
        }
    }

    void _onKeyDownSave(wxKeyEvent &event)
    {
        if ((_keyCode == 83 && 308 == (int)event.GetKeyCode()) ||
            (_keyCode == 308 && 83 == (int)event.GetKeyCode()))
        {
            if (_showMessageBox(std::string("You want save?")))
                _subject->setTreeNodeContentById(_tree->GetFocusedItem(), _wxStringToStdString(_text->GetValue()));
            _keyCode = 0;
        }
        else
            _keyCode = (int)event.GetKeyCode();

        event.Skip();
    }

    void _endNodeNameEdit(wxTreeEvent &event)
    {
        // wxCharBuffer buffer = event.GetLabel().mb_str();
        // std::string newLabel = buffer.data();
        std::string newLabel = _wxStringToStdString(event.GetLabel());
        std::smatch match;
        std::regex matchName(".+?(?=,)");
        std::regex_search(newLabel, match, matchName);
        std::string oldName = _subject->getNodeById(event.GetItem())->name();
        std::string newName = match.str(0);
        int size = _subject->getNodeById(event.GetItem())->size();

        if (oldName != newName)
        {
            if (_showMessageBox(std::string("label edited:" + newName + ", " + std::to_string(size) + "-- old name was " + oldName)))
            {
                _subject->setNodeName(event.GetItem(), newName);
                return;
            }
        }
        wxString oldNodeName(std::string(oldName + ", " + std::to_string(size)));
        _tree->SetItemText(event.GetItem(), oldNodeName);
        _tree->Refresh();
        event.Veto();
    }

    bool _showMessageBox(std::string message)
    {
        wxMessageDialog *dial = new wxMessageDialog(this, message, wxT("Confirm"), wxYES_NO | wxCANCEL | wxICON_QUESTION);

        if (dial->ShowModal() == wxID_YES)
            return 1;
        return 0;
    }

    wxTreeItemId _getwxTreeItemId(wxMouseEvent &event)
    {
        wxPoint pt = event.GetPosition();
        int flag = 0;
        return _tree->HitTest(pt, flag);
    }

    std::string _wxStringToStdString(wxString wxstring)
    {
        wxCharBuffer buffer = wxstring.mb_str();
        return buffer.data();
    }
};

BEGIN_EVENT_TABLE(TreeFrame, wxFrame)
EVT_TREE_END_LABEL_EDIT(wxID_ANY, TreeFrame::_endNodeNameEdit)
EVT_KEY_DOWN(TreeFrame::_onKeyDownSave)
END_EVENT_TABLE()
#endif
