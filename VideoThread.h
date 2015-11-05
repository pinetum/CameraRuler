#ifndef VIDEOTHREAD_H
#define VIDEOTHREAD_H

#include <wx/thread.h> // Base class: wxThread
#include <opencv2/opencv.hpp>
#include <wx/event.h>


wxDECLARE_EVENT(wxEVT_COMMAND_VIDEO_START, wxThreadEvent);
wxDECLARE_EVENT(wxEVT_COMMAND_VIDEO_COMPLETED, wxThreadEvent);
wxDECLARE_EVENT(wxEVT_COMMAND_VIDEO_UPDATE, wxThreadEvent);
class VideoThread : public wxThread
{
	
public:
	VideoThread(wxEvtHandler* parent, int intervalTime, wxString VideoFile);
	VideoThread(wxEvtHandler* parent, int DeviceNumber);
	wxEvtHandler* m_pHandler;
	~VideoThread();
	cv::VideoCapture m_Vcam;
	int m_nTotalFrames;
	int m_nFrameCounter;
	int m_nVideoFrameRate;
	int m_nDeviceNumber;
	bool m_bDrawPoints;
	int m_nIntervalTime;
	wxString m_strFilePath;
	virtual ExitCode Entry();
};

#endif // VIDEOTHREAD_H
