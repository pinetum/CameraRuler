#include "MainFrame.h"
#include <wx/aboutdlg.h>
#include <wx/filedlg.h>
#include <wx/dcclient.h>


wxDEFINE_EVENT(wxEVT_COMMAND_VIDEO_START,           wxThreadEvent);
wxDEFINE_EVENT(wxEVT_COMMAND_VIDEO_COMPLETED,       wxThreadEvent);
wxDEFINE_EVENT(wxEVT_COMMAND_VIDEO_UPDATE,          wxThreadEvent);






MainFrame::MainFrame(wxWindow* parent)
    : MainFrameBaseClass(parent)
{
    int statuWidth[4]   = { 250, 80, 40, 140};
	m_statusBar->SetFieldsCount(4, statuWidth);
	
    
    
    m_vThread = NULL;
    Center();
    m_bThreadRunning = false;
    //Maximize(true);
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
void MainFrame::clearAll()
{
    m_radioBoxPoints->SetSelection(0);
    for(int i =0; i < COUNT_PTS; i++)
    {
        m_points[i][0]=0.0;
        m_points[i][1]=0.0;
        m_points[i][2]=0.0;
    }
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
    if(m_img.data == NULL)
        return;
    //get mouse position
    wxClientDC dc(this);
	wxPoint pt1 = event.GetLogicalPosition(dc);
	wxPoint pt ;
	m_scrollWin->CalcUnscrolledPosition(pt1.x,pt1.y,&pt.x,&pt.y);
    showMessage(wxString::Format("[Mouse Click] %d,%d", pt.x, pt.y));
    int pt_index = m_radioBoxPoints->GetSelection();
    //showMessage(wxString::Format("%d", pt_index));
    m_points[pt_index][0] = pt.x;
    m_points[pt_index][1] = pt.y;
    m_points[pt_index][2] = 1;
    updateLines();
    pt_index++;
    if( pt_index == m_radioBoxPoints->GetRowCount())
        pt_index = 0;
    m_radioBoxPoints->SetSelection(pt_index);
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
    
    clearAll();
    
    
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
void MainFrame::updateLines()
{
    cv::Mat drawedLineMat = m_img.clone();
    getResult();
    drawPoints(drawedLineMat);
    drawStraightLine(drawedLineMat);
    
    m_scrollWin->setImage(drawedLineMat);
    //cv::Point3d 
}
void MainFrame::drawPoints(cv::Mat &img)
{
    cv::RNG rng(12345);
    for(int i=0; i<COUNT_PTS; i++)
    {
        cv::Point pt;
        pt.x = m_points[i][0];
        pt.y = m_points[i][1];
        if(pt.x == 0 && pt.y == 0)
            break;
        cv::circle(img, pt, 2, cv::Scalar(rng.uniform(0,255), rng.uniform(0, 255), rng.uniform(0, 255)) ,2);
        
    }
}
void MainFrame::drawStraightLine(cv::Mat &img)
{
    
// 把線存成ax+by+c=0
// 用外積可以找交點
//  top_horizontal =    [0 1 0];
//  left_vertical   =   [1 0 0];
//  bottom_horizontal = [0 1 -image.rows];
//  right_vertical =    [1 0 -image.cols];
    cv::Vec3d top(0, 1, 0);
    cv::Vec3d left(1, 0, 0);
    cv::Vec3d btm(0, 1, m_img.rows*-1);
    cv::Vec3d right(1, 0, m_img.cols*-1);
    
    cv::RNG rng(33333);
    for(int i =0; i< COUNT_LINES; i++)
    {
        cv::Point pt_line_begin, pt_line_end;
        if(m_lines[i][0] == 0 && m_lines[i][1] == 0 && m_lines[i][01] == 0 )
            break;
        cv::Vec3d pt3d[4];
        pt3d[0] = m_lines[i].cross(top);
        pt3d[1] = m_lines[i].cross(btm);
        pt3d[2] = m_lines[i].cross(left);
        pt3d[3] = m_lines[i].cross(right);
        
        for(int j = 0; j<4; j++)
        {
            if(abs(pt3d[j][2])>0.0001)
            {
                pt3d[j][0] = pt3d[j][0]/pt3d[j][2];
                pt3d[j][1] = pt3d[j][1]/pt3d[j][2];
            }
            //showMessage(wxString::Format("%f,%f,%f", pt3d[j][0], pt3d[j][1], pt3d[j][2]));
        }
        //上左
        if( pt3d[0][0]<m_img.cols && pt3d[0][1]<m_img.rows && !pt3d[0][0] < 0 && !pt3d[0][1] <0)
        {
            pt_line_begin.x = pt3d[0][0];
            pt_line_begin.y = pt3d[0][1];
        }
        else
        {
            pt_line_begin.x = pt3d[2][0];
            pt_line_begin.y = pt3d[2][1];
        }
        //右下
        if( pt3d[1][0]<m_img.cols && pt3d[1][1]<m_img.rows && !pt3d[1][0]< 0  && !pt3d[1][1] <0)
        {
            pt_line_end.x = pt3d[1][0];
            pt_line_end.y = pt3d[1][1];
        }
        else
        {
            pt_line_end.x = pt3d[3][0];
            pt_line_end.y = pt3d[3][1];
        }
        
        cv::line(img, pt_line_begin, pt_line_end, cv::Scalar(rng.uniform(0,255), rng.uniform(0, 255), rng.uniform(0, 255)), 2);
        
        showMessage(wxString::Format("[Draw Line]%d, %d <--->  %d, %d", pt_line_begin.x, pt_line_begin.y, pt_line_end.x, pt_line_end.y));
        
        
    }
        
}
void MainFrame::OnKeyDown(wxKeyEvent& event)
{
    //showMessage(wxString::Format("[Key Down] %d", event.GetKeyCode()));
}
void MainFrame::OnNextSelection(wxCommandEvent& event)
{
    int sel = m_radioBoxPoints->GetSelection()+1;
    
    if(sel == m_radioBoxPoints->GetRowCount())
        sel = 0;
    m_radioBoxPoints->SetSelection(sel);
}
void MainFrame::getResult()
{
    //算平行線
    
    m_lines[VX_LINE1] = m_points[VX_PARLLEL_LINE1_P1].cross(m_points[VX_PARLLEL_LINE1_P2]);
    m_lines[VX_LINE2] = m_points[VX_PARLLEL_LINE2_P1].cross(m_points[VX_PARLLEL_LINE2_P2]);
    m_lines[VY_LINE1] = m_points[VY_PARLLEL_LINE1_P1].cross(m_points[VY_PARLLEL_LINE1_P2]);
    m_lines[VY_LINE2] = m_points[VY_PARLLEL_LINE2_P1].cross(m_points[VY_PARLLEL_LINE2_P2]);
    m_lines[VZ_LINE1] = m_points[VZ_PARLLEL_LINE1_P1].cross(m_points[VZ_PARLLEL_LINE1_P2]);
    m_lines[VZ_LINE2] = m_points[VZ_PARLLEL_LINE2_P1].cross(m_points[VZ_PARLLEL_LINE2_P2]);

    //算消失點
    m_points[VNISH_H1] = m_lines[VX_LINE1].cross(m_lines[VX_LINE2]);
    m_points[VNISH_H2] = m_lines[VY_LINE1].cross(m_lines[VY_LINE2]);
    m_points[VNISH_V] = m_lines[VZ_LINE1].cross(m_lines[VZ_LINE2]);
    
    for(int j = VNISH_H1; j<=VNISH_V; j++)
    {
        if(abs(m_points[j][2])>0.0001)
        {
            m_points[j][0] = m_points[j][0]/m_points[j][2];
            m_points[j][1] = m_points[j][1]/m_points[j][2];
            m_points[j][2] = 1;
        }
    }
    m_staticTextVanishP1->SetLabel(wxString::Format("%d, %d",(int)m_points[VNISH_H1][0], (int)m_points[VNISH_H1][1]));
    m_staticTextVanishP2->SetLabel(wxString::Format("%d, %d",(int)m_points[VNISH_H2][0], (int)m_points[VNISH_H2][1]));
    
    //算消失線
    m_lines[VANIS_LINE] = m_points[VNISH_H1].cross(m_points[VNISH_H2]);
    
}
void MainFrame::OnClickClearAll(wxCommandEvent& event)
{
    clearAll();
}
