

#pragma once

#include "MediaStreamSinkDialogData.h"
#include "Dialogs.h"

class CVideoCaptureDialogData
{
public:
	CVideoCaptureDialogData( _DSHOWLIB_NAMESPACE::Grabber& grabber );
	CVideoCaptureDialogData( _DSHOWLIB_NAMESPACE::Grabber& grabber, smart_ptr<tMediaStreamSinkDialogSettings> pInitialSettings );
	~CVideoCaptureDialogData();

    bool	isRecording();
	void	pause();
	bool	isPaused();
	void	start();
	void	stop();

	std::wstring	getContainer();
	std::wstring	getCodec();
	std::wstring	getFilename();

	std::wstring getRecordedTimeString();

	smart_ptr<_DSHOWLIB_NAMESPACE::MediaStreamSink>	getSink();
	void	setSink( smart_ptr<_DSHOWLIB_NAMESPACE::MediaStreamSink> pSink );

	smart_ptr<tMediaStreamSinkDialogSettings>		getDialogSettings();

private:
	CMediaStreamSinkDialogData						m_sinkData;

	smart_ptr<_DSHOWLIB_NAMESPACE::MediaStreamSink>	m_pOldSink;
	bool											m_bOldLive;

	_DSHOWLIB_NAMESPACE::Grabber&					m_Grabber;
	bool											m_bPaused;
	bool											m_bRecording;

	REFERENCE_TIME									m_recordedTime;
	REFERENCE_TIME									m_startTime;
};
