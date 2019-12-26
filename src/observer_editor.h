#ifndef OBSERVR_EDITOR_H
#define OBSERVR_EDITOR_H

#include <wx/treectrl.h>
#include <wx/textctrl.h>
#include <wx/button.h>
#include <string>
#include "concrete_subject.h"
#include "observer.h"

class ObserverEditor : public Observer
{
public:
    ObserverEditor(ConcreteSubject *s, wxTextCtrl *t, wxButton *b) : _subject(s), _text(t), _button(b) {}

    void setValue(wxTreeItemId clickedId)
    {
        std::string content = _subject->getTreeNodeContentById(clickedId);
        _text->SetValue(content);
        if (content != "The file is not displayed in the editor because it uses an unsupported text encoding." && content != "")
        {
            _text->Enable(true);
            _button->Enable(true);
        }
        else
        {
            _text->Enable(false);
            _button->Enable(false);
        }
    }

    void update(wxTreeItemId savedFileId) override
    {

    }

private:
    ConcreteSubject *_subject;
    wxTextCtrl *_text;
    wxButton *_button;
};

#endif