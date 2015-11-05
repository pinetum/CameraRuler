//////////////////////////////////////////////////////////////////////
// This file was auto-generated by codelite's wxCrafter Plugin
// wxCrafter project file: wxcrafter.wxcp
// Do not modify this file by hand!
//////////////////////////////////////////////////////////////////////

#ifndef CODING_CAMERARULER_WXCRAFTER_BASE_CLASSES_H
#define CODING_CAMERARULER_WXCRAFTER_BASE_CLASSES_H

#include <wx/settings.h>
#include <wx/xrc/xmlres.h>
#include <wx/xrc/xh_bmp.h>
#include <wx/frame.h>
#include <wx/iconbndl.h>
#include <wx/artprov.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/scrolwin.h>
#include "MyImageWin.h"
#include <wx/radiobox.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/richtext/richtextctrl.h>
#include <wx/menu.h>
#include <wx/toolbar.h>
#include <wx/statusbr.h>
#if wxVERSION_NUMBER >= 2900
#include <wx/persist.h>
#include <wx/persist/toplevel.h>
#include <wx/persist/bookctrl.h>
#include <wx/persist/treebook.h>
#endif

class MainFrameBaseClass : public wxFrame
{
public:
    enum {
        wxID_OPEN_FILE = 1001,
    };
protected:
    wxPanel* m_mainPanel;
    MyImageWin* m_scrollWin;
    wxRadioBox* m_radioBoxPoints;
    wxStaticText* m_staticText87;
    wxStaticText* m_staticTextVanishP1;
    wxStaticText* m_staticText91;
    wxStaticText* m_staticTextVanishP2;
    wxStaticText* m_staticText95;
    wxStaticText* m_staticTextObjectTB;
    wxStaticText* m_staticText99;
    wxStaticText* m_staticTextTargetTB;
    wxStaticText* m_staticText73;
    wxTextCtrl* m_textCtrlOBJh;
    wxStaticText* m_staticText77;
    wxStaticText* m_staticTextAnswer;
    wxRichTextCtrl* m_richTextCtrl;
    wxMenuBar* m_menuBar;
    wxMenu* m_name6;
    wxMenuItem* m_menuItem81;
    wxMenuItem* m_menuItem7;
    wxMenu* m_name8;
    wxMenuItem* m_menuItem9;
    wxMenu* m_menu21;
    wxMenuItem* m_menuItemCam;
    wxMenuItem* m_menuItemFile;
    wxToolBar* m_mainToolbar;
    wxStatusBar* m_statusBar;

protected:
    virtual void OnMouseLD(wxMouseEvent& event) { event.Skip(); }
    virtual void OnMouseMotion(wxMouseEvent& event) { event.Skip(); }
    virtual void OnFileOpen(wxCommandEvent& event) { event.Skip(); }
    virtual void OnExit(wxCommandEvent& event) { event.Skip(); }
    virtual void OnAbout(wxCommandEvent& event) { event.Skip(); }
    virtual void OnMenuCamera(wxCommandEvent& event) { event.Skip(); }
    virtual void OnMenuFileOpen(wxCommandEvent& event) { event.Skip(); }

public:
    MyImageWin* GetScrollWin() { return m_scrollWin; }
    wxRadioBox* GetRadioBoxPoints() { return m_radioBoxPoints; }
    wxStaticText* GetStaticText87() { return m_staticText87; }
    wxStaticText* GetStaticTextVanishP1() { return m_staticTextVanishP1; }
    wxStaticText* GetStaticText91() { return m_staticText91; }
    wxStaticText* GetStaticTextVanishP2() { return m_staticTextVanishP2; }
    wxStaticText* GetStaticText95() { return m_staticText95; }
    wxStaticText* GetStaticTextObjectTB() { return m_staticTextObjectTB; }
    wxStaticText* GetStaticText99() { return m_staticText99; }
    wxStaticText* GetStaticTextTargetTB() { return m_staticTextTargetTB; }
    wxStaticText* GetStaticText73() { return m_staticText73; }
    wxTextCtrl* GetTextCtrlOBJh() { return m_textCtrlOBJh; }
    wxStaticText* GetStaticText77() { return m_staticText77; }
    wxStaticText* GetStaticTextAnswer() { return m_staticTextAnswer; }
    wxRichTextCtrl* GetRichTextCtrl() { return m_richTextCtrl; }
    wxPanel* GetMainPanel() { return m_mainPanel; }
    wxMenuBar* GetMenuBar() { return m_menuBar; }
    wxToolBar* GetMainToolbar() { return m_mainToolbar; }
    wxStatusBar* GetStatusBar() { return m_statusBar; }
    MainFrameBaseClass(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("My Frame"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(800,800), long style = wxCAPTION|wxRESIZE_BORDER|wxMAXIMIZE_BOX|wxMINIMIZE_BOX|wxSYSTEM_MENU|wxCLOSE_BOX);
    virtual ~MainFrameBaseClass();
};

#endif
