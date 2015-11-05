#include "VideoThread.h"
#include <wx/event.h> 



VideoThread::VideoThread(wxEvtHandler* parent, int DeviceNumber)
{
	m_Vcam.open(DeviceNumber);
	m_pHandler = parent;
	m_nTotalFrames = 1;
	m_nFrameCounter = 0;
	m_nVideoFrameRate = 0;
	m_nDeviceNumber = DeviceNumber;
	m_bDrawPoints = true;
	m_strFilePath = "";
	
}
VideoThread::VideoThread(wxEvtHandler* parent,int intervalTime, wxString VideoFile)
{
	m_Vcam.open(VideoFile.ToStdString());
	m_pHandler = parent;
	m_nIntervalTime = intervalTime;
	m_nTotalFrames = 1;
	m_nFrameCounter = 0;
	m_nVideoFrameRate = 0;
	m_nDeviceNumber = -1 ;
	m_nTotalFrames = m_Vcam.get(CV_CAP_PROP_FRAME_COUNT);
	m_nVideoFrameRate = m_Vcam.get(CV_CAP_PROP_FPS);
	m_bDrawPoints = true;
	m_strFilePath = VideoFile;
}

VideoThread::~VideoThread()
{
	if(m_Vcam.isOpened())
	{
        m_Vcam.release();
    }
	
	
}
wxThread::ExitCode VideoThread::Entry()
{
	wxThreadEvent* evt_s;
    evt_s = new wxThreadEvent(wxEVT_COMMAND_VIDEO_START);
//	if(m_nDeviceNumber == -1 ){
//		evt_s->SetInt(m_nTotalFrames);
//		evt_s->SetString(wxString::Format("Total Frames:%d\nVideo fps:%d\n",m_nTotalFrames,m_nVideoFrameRate));
//		ndelayFrame = m_nVideoFrameRate * m_nIntervalTime /1000;
//	}
//	else{
//		evt_s->SetString(wxString::Format("Camera:%d(%.0fx%.0f)",m_nDeviceNumber,m_Vcam.get(CV_CAP_PROP_FRAME_WIDTH),m_Vcam.get(CV_CAP_PROP_FRAME_HEIGHT)));
//		Sleep(1000);
//	}
	wxQueueEvent(m_pHandler, evt_s);
	cv::Mat frame;
    wxThreadEvent * evt ;
	while(!TestDestroy() && m_Vcam.grab() && m_Vcam.isOpened()){
		m_Vcam.retrieve(frame);
		evt = new wxThreadEvent(wxEVT_COMMAND_VIDEO_UPDATE);
        evt->SetPayload(frame);
		wxQueueEvent(m_pHandler, evt);
		cvWaitKey(10);
		
	}
	m_Vcam.release();
	wxQueueEvent(m_pHandler,  new wxThreadEvent(wxEVT_COMMAND_VIDEO_COMPLETED) );
	return (wxThread::ExitCode)0;
}
