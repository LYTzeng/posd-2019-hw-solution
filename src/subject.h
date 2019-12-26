#ifndef SUBJECT_H
#define SUBJECT_H

#include "observer.h"
#include <vector>
#include <iterator>
#include <wx/treectrl.h>

class Subject
{
public:
    Subject(){}

    virtual void attach(Observer *observer) = 0;

    virtual void detach(Observer *observer) = 0;

    virtual void notify(wxTreeItemId savedFileId) = 0;

protected:
    std::vector<Observer *> observers;
};

#endif
