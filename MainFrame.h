#ifndef MAINFRAME_H
#define MAINFRAME_H
#include "wxcrafter.h"
#include "VideoThread.h"




class MainFrame : public MainFrameBaseClass
{
public:
    MainFrame(wxWindow* parent);
    virtual ~MainFrame();
    VideoThread* m_vThread;
    cv::Mat m_img;
    bool m_bThreadRunning;
    void clearThread();
    void OnVideoThreadUpdate(wxThreadEvent& event);
    void OnVideoThreadStart(wxThreadEvent& event);
    void OnVideoThreadComplete(wxThreadEvent& event);
    void showMessage(wxString msg);
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    double getObjectActualyHeight();
protected:
    virtual void OnMenuFileOpen(wxCommandEvent& event);
    virtual void OnMouseMotion(wxMouseEvent& event);
    virtual void OnFileOpen(wxCommandEvent& event);
    virtual void OnMouseLD(wxMouseEvent& event);
    virtual void OnMenuCamera(wxCommandEvent& event);
};
#endif // MAINFRAME_H
