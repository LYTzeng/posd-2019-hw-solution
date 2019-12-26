#ifndef OBSERVER_H
#define OBSERVER_H

#include <wx/treectrl.h>

class Observer
{
public:
    virtual void update(wxTreeItemId savedFileId) = 0;
};

#endif