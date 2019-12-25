#include <wx/wx.h>
#include "ui_folder_tree.h"
#include "tree_frame.h"

IMPLEMENT_APP(FolderTreeApp)

bool FolderTreeApp::OnInit()
{
    wxCharBuffer buffer = wxApp::argv[1].mb_str();
    wxFrame *frame = new TreeFrame(wxT("***Tree Test***"), 100, 100, 1000, 600, buffer.data());
    frame->Show(true);
    SetTopWindow(frame);
    return true;
}
