#ifndef MAINFRAME_H
#define MAINFRAME_H
#include "wxcrafter.h"
#include "VideoThread.h"
#include <vector>

#define COUNT_PTS               21

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
#define VNISH_H1               16
#define VNISH_H2               17
#define VNISH_V                18
#define ANS_ONVNISH             19
#define ANS_ONOBJ               20

#define COUNT_LINES             10

#define VX_LINE1                 0
#define VX_LINE2                 1
#define VY_LINE1                 2
#define VY_LINE2                 3
#define VZ_LINE1                 4
#define VZ_LINE2                 5
#define VANIS_LINE               6
#define ANS_T_LINE               7
#define ANS_B_LINE               8
#define OBJ_TB_LINE              9

class MainFrame : public MainFrameBaseClass
{
public:
    MainFrame(wxWindow* parent);
    virtual ~MainFrame();
    VideoThread* m_vThread;
    cv::Mat m_img;
    cv::Vec3d m_points[COUNT_PTS];
    
    cv::Vec3d m_lines[COUNT_LINES];
    
    void getAnswer();
    void getResult();
    void clearAll();
    bool m_bThreadRunning;
    void drawPoints(cv::Mat &img);
    void rescalePt(cv::Vec3d &pt);
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
    virtual void OnTextctrlobjhTextUpdated(wxCommandEvent& event);
    virtual void OnClickClearAll(wxCommandEvent& event);
    virtual void OnNextSelection(wxCommandEvent& event);
    virtual void OnKeyDown(wxKeyEvent& event);
    virtual void OnMenuFileOpen(wxCommandEvent& event);
    virtual void OnMouseMotion(wxMouseEvent& event);
    virtual void OnFileOpen(wxCommandEvent& event);
    virtual void OnMouseLD(wxMouseEvent& event);
    virtual void OnMenuCamera(wxCommandEvent& event);
};
#endif // MAINFRAME_H
