#include "MainFrame.h"
#include <wx/aboutdlg.h>
#include <wx/filedlg.h>
#include <wx/dcclient.h>


wxDEFINE_EVENT(wxEVT_COMMAND_VIDEO_START,           wxThreadEvent);
wxDEFINE_EVENT(wxEVT_COMMAND_VIDEO_COMPLETED,       wxThreadEvent);
wxDEFINE_EVENT(wxEVT_COMMAND_VIDEO_UPDATE,          wxThreadEvent);



#define COUNT_PTS           16;

#define VX_PARLLEL_LINE1_P1     0;
#define VX_PARLLEL_LINE1_P2     1;
#define VX_PARLLEL_LINE2_P1     2;
#define VX_PARLLEL_LINE2_P2     3;
#define VY_PARLLEL_LINE1_P1     4;
#define VY_PARLLEL_LINE1_P2     5;
#define VY_PARLLEL_LINE2_P1     6;
#define VY_PARLLEL_LINE2_P2     7;
#define VZ_PARLLEL_LINE1_P1     8;
#define VZ_PARLLEL_LINE1_P2     9;
#define VZ_PARLLEL_LINE2_P1     10;
#define VZ_PARLLEL_LINE2_P2     11;
#define OBJECT_T                12;
#define OBJECT_B                13;
#define TARGET_T                14;
#define TARGET_B                15;



MainFrame::MainFrame(wxWindow* parent)
    : MainFrameBaseClass(parent)
{
    int statuWidth[4]   = { 250, 80, 40, 140};
	m_statusBar->SetFieldsCount(4, statuWidth);
	
    m_vThread = NULL;
    Center();
    m_bThreadRunning = false;
    Maximize(true);
    Bind(wxEVT_COMMAND_VIDEO_START, &MainFrame::OnVideoThreadStart, this);
    Bind(wxEVT_COMMAND_VIDEO_COMPLETED, &MainFrame::OnVideoThreadComplete, this);
    Bind(wxEVT_COMMAND_VIDEO_UPDATE, &MainFrame::OnVideoThreadUpdate, this);
    
}
MainFrame::~MainFrame()
{
    clearThread();
}
void MainFrame::clearThread()
{
    if(m_vThread!= NULL)
    {
        m_vThread->Delete();
        m_vThread = NULL;
    }
    
}
void MainFrame::OnExit(wxCommandEvent& event)
{
    
    wxUnusedVar(event);
    Close();
}

void MainFrame::OnAbout(wxCommandEvent& event)
{
    wxUnusedVar(event);
    wxAboutDialogInfo info;
    info.SetCopyright(_("My MainFrame"));
    info.SetLicence(_("GPL v2 or later"));
    info.SetDescription(_("Short description goes here"));
    ::wxAboutBox(info);
}
void MainFrame::OnMenuCamera(wxCommandEvent& event)
{
    if(m_bThreadRunning)
        clearThread();
    else
    {
        m_vThread = new VideoThread(this, 0);
        m_vThread->Run();
    }
        
}

void MainFrame::showMessage(wxString msg)
{
    m_richTextCtrl->AppendText(msg << "\n");
    int last_pos = m_richTextCtrl->GetLastPosition();
    m_richTextCtrl->ShowPosition(last_pos);
}
void MainFrame::OnVideoThreadUpdate(wxThreadEvent& event)
{
    m_img = event.GetPayload<cv::Mat>();
    //showMessage(wxString::Format("%d,%d", img.rows, img.cols));
    m_scrollWin->setImage(m_img);
}
void MainFrame::OnVideoThreadStart(wxThreadEvent& event)
{
    m_bThreadRunning = true;
    m_menuItemCam->SetText("Stop Camera...");
    showMessage("start");
}
void MainFrame::OnVideoThreadComplete(wxThreadEvent& event)
{
    m_bThreadRunning = false;
    m_menuItemCam->SetText("Start Camera...");
    showMessage("stop");
}
void MainFrame::OnMouseLD(wxMouseEvent& event)
{
    
    //get mouse position
    wxClientDC dc(this);
	wxPoint pt1 = event.GetLogicalPosition(dc);
	wxPoint pt ;
	m_scrollWin->CalcUnscrolledPosition(pt1.x,pt1.y,&pt.x,&pt.y);
    showMessage(wxString::Format("[Mouse Click] %d,%d", pt.x, pt.y));
    
    
    
    
    
}
void MainFrame::OnFileOpen(wxCommandEvent& event)
{
    wxString fileType = _("All suported graphic formats(*.jpg,*.bmp,*.jpeg,*.*.png)|*.jpg;*.bmp;*.jpeg;*.png;*.tif");
	wxFileDialog* openDialog = new wxFileDialog(this,_("openFile"),wxEmptyString,wxEmptyString,fileType,wxFD_OPEN,wxDefaultPosition);
	if(openDialog->ShowModal() == wxID_OK){
		wxString pathName = openDialog->GetPath();
		m_img = cv::imread(pathName.ToStdString());
        m_scrollWin->setImage(m_img);
    }
	
	openDialog->Destroy();
    
    
    
    
}
void MainFrame::OnMouseMotion(wxMouseEvent& event)
{
    // get position in the scroll win 
	wxClientDC dc(this);
	wxPoint pt1 = event.GetLogicalPosition(dc); // position in screen in scrollwin
	wxPoint pt ; // position in "scrllWin" (mouse on image's position)
	m_scrollWin->CalcUnscrolledPosition(pt1.x,pt1.y,&pt.x,&pt.y);
	
    // get image information..
	
	if(!m_img.data) return;
	cv::Size sz = m_img.size();
	if(pt.x >=sz.width || pt.y >= sz.height) return;
	
    
    // setting staturBar info string:image type and num of channel and depth
    wxString str;
	int type = m_img.type();
	switch(type){
			case CV_8UC3:{
				cv::Vec3b c = m_img.at<cv::Vec3b>(pt.x, pt.y);
				uchar b = c.val[0];
				uchar g = c.val[1];
				uchar r = c.val[2];
				str.Printf("(%d, %d) [%d %d %d]", pt.x, pt.y, r, g, b); }
				break;
			case CV_8UC4:{
				
                cv::Vec4b c = m_img.at<cv::Vec4b>(pt.x, pt.y);
				uchar b = c.val[0];
				uchar g = c.val[1];
				uchar r = c.val[2];
				uchar u = c.val[3];
				str.Printf("(%d, %d) [%d %d %d %d]", pt.x, pt.y, r, g, b,u);}
				break;
			case CV_8UC1: {
				uchar c = m_img.at<uchar>(pt.x, pt.y);
				str.Printf("(%d, %d) [%d]", pt.x, pt.y, c); }
				break; 
			case CV_16UC1: {
				ushort c = m_img.at<ushort>(pt.x, pt.y);
				str.Printf("(%d, %d) [%d]", pt.x, pt.y, c); }
				break;
			case CV_16SC1: {
				short c = m_img.at<short>(pt.x, pt.y);
				str.Printf("(%d, %d) [%d]", pt.x, pt.y, c); }
				break;
			case CV_32FC1: {
				float c = m_img.at<float>(pt.x, pt.y);
 				str.Printf("(%d, %d) [%.3f]", pt.x, pt.y, c); }
				break;
			case CV_64FC1: {
				double c = m_img.at<double>(pt.x, pt.y);
				
				str.Printf("(%d, %d) [%.4f]", pt.x, pt.y, c); }
				break;
				
		}
	m_statusBar->SetStatusText(str, 3);
    
    
}
double MainFrame::getObjectActualyHeight(){
    wxString val = m_textCtrlOBJh->GetValue();
    double d_val = 0;
    val.ToDouble(&d_val);
    return d_val;
}
void MainFrame::OnMenuFileOpen(wxCommandEvent& event)
{
}
