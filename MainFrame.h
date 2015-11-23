#ifndef MAINFRAME_H
#define MAINFRAME_H
#include "wxcrafter.h"
#include "VideoThread.h"
#include <vector>

#define COUNT_PTS               16

#define VX_PARLLEL_LINE1_P1     0
#define VX_PARLLEL_LINE1_P2     1
#define VX_PARLLEL_LINE2_P1     2
#define VX_PARLLEL_LINE2_P2     3
#define VY_PARLLEL_LINE1_P1     4
#define VY_PARLLEL_LINE1_P2     5
#define VY_PARLLEL_LINE2_P1     6
#define VY_PARLLEL_LINE2_P2     7
#define VZ_PARLLEL_LINE1_P1     8
#define VZ_PARLLEL_LINE1_P2     9
#define VZ_PARLLEL_LINE2_P1     10
#define VZ_PARLLEL_LINE2_P2     11
#define OBJECT_T                12
#define OBJECT_B                13
#define TARGET_T                14
#define TARGET_B                15


#define COUNT_LINES             6

#define VX_LINE1                 0
#define VX_LINE2                 1
#define VY_LINE1                 2
#define VY_LINE2                 3
#define VZ_LINE1                 4
#define VZ_LINE2                 5


class MainFrame : public MainFrameBaseClass
{
public:
    MainFrame(wxWindow* parent);
    virtual ~MainFrame();
    VideoThread* m_vThread;
    cv::Mat m_img;
    cv::Vec3d m_points[COUNT_PTS];
    
    cv::Vec3d m_lines[COUNT_LINES];
    
    
    bool m_bThreadRunning;
    void drawPoints(cv::Mat &img);
    void clearThread();
    void updateLines();
    void OnVideoThreadUpdate(wxThreadEvent& event);
    void OnVideoThreadStart(wxThreadEvent& event);
    void OnVideoThreadComplete(wxThreadEvent& event);
    void drawStraightLine(cv::Mat &img);
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
