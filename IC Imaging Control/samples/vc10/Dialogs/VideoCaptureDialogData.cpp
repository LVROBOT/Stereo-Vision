
#include "stdafx.h"
#include "VideoCaptureDialogData.h"

#include <strsafe.h>

using namespace _DSHOWLIB_NAMESPACE;

CVideoCaptureDialogData::CVideoCaptureDialogData( _DSHOWLIB_NAMESPACE::Grabber& grabber )
	:	m_bPaused( false ),
		m_Grabber( grabber ),
		m_bRecording( false ),
		m_sinkData( grabber.getSinkTypePtr() )
{
}

CVideoCaptureDialogData::CVideoCaptureDialogData( _DSHOWLIB_NAMESPACE::Grabber& grabber, smart_ptr<tMediaStreamSinkDialogSettings> pInitialSettings )
	:	m_bPaused( false ),
		m_Grabber( grabber ),
		m_bRecording( false )
{
	if( pInitialSettings != 0 )
	{
		MediaStreamSink::tMSSPtr tmpSink = MediaStreamSink::create( pInitialSettings->sinkData );
		tmpSink->setFilename( pInitialSettings->fileName );

		m_sinkData = CMediaStreamSinkDialogData( tmpSink );
	}
	else
	{
		m_sinkData = CMediaStreamSinkDialogData( grabber.getSinkTypePtr() );
	}
}

CVideoCaptureDialogData::~CVideoCaptureDialogData()
{
}


bool	CVideoCaptureDialogData::isRecording()
{
	return m_bRecording;
}

void	CVideoCaptureDialogData::pause()
{
	m_bPaused = !m_bPaused;
	if( isRecording() )
	{
		if( m_bPaused )
		{
			REFERENCE_TIME now;
			m_Grabber.getCurReferenceTime( now );
			m_recordedTime += (now - m_startTime);
		}

		m_Grabber.getSinkType().setSinkMode( m_bPaused ? GrabberSinkType::ePAUSE : GrabberSinkType::eRUN );

		if( !m_bPaused )
		{
			m_Grabber.getCurReferenceTime( m_startTime );
		}
	}	
}

bool	CVideoCaptureDialogData::isPaused()
{
	return m_bPaused;
}

void	CVideoCaptureDialogData::start()
{
	m_pOldSink = m_Grabber.getSinkTypePtr();
	m_bOldLive = m_Grabber.isLive();

	smart_ptr<MediaStreamSink> pSink = m_sinkData.createSink();
	if( pSink == 0 )
	{
		MessageBox( 0, TEXT("Unable to create FileWriter Sink"), TEXT("Error"), MB_OK|MB_ICONERROR );
		return;
	}
	else
	{
		if( m_bOldLive )
		{
			m_Grabber.stopLive();
		}

		pSink->setSinkMode( m_bPaused ? GrabberSinkType::ePAUSE : GrabberSinkType::eRUN );
		m_Grabber.setSinkType( pSink );

		if( !m_Grabber.startLive() )
		{
			MessageBox( 0, TEXT("Failed to start live mode"), TEXT("Error"), MB_OK|MB_ICONERROR );
			return;
		}

		m_Grabber.getGraphStartReferenceTime( m_startTime );
		m_recordedTime = 0;

		m_bRecording = true;
	}

}

void	CVideoCaptureDialogData::stop()
{
	REFERENCE_TIME now;
	m_Grabber.getCurReferenceTime( now );
	m_recordedTime += (now - m_startTime);

	m_bRecording = false;
	m_Grabber.stopLive();

	m_Grabber.setSinkType( m_pOldSink );
	if( m_bOldLive )
	{
		if( !m_Grabber.startLive() )
		{
			MessageBox( 0, TEXT("Failed to start live mode"), TEXT("Error"), MB_OK|MB_ICONERROR );
			return;
		}
	}
}

std::wstring	CVideoCaptureDialogData::getContainer()
{
	return m_sinkData.getSelectedContainer()->toStringW();
}

std::wstring	CVideoCaptureDialogData::getCodec()
{
	switch( m_sinkData.getSelectedContainerType() )
	{
	case eCodec:
		return m_sinkData.getSelectedCodec()->toStringW();
	case eUncompressed:
		return m_sinkData.getSelectedUCFormatName();
	case eUnspecified:
	default:
		return L"";
	}
}

std::wstring	CVideoCaptureDialogData::getFilename()
{
	return m_sinkData.getFilename();
}

smart_ptr<MediaStreamSink> CVideoCaptureDialogData::getSink()
{
	return m_sinkData.createSink();
}

smart_ptr<tMediaStreamSinkDialogSettings>		CVideoCaptureDialogData::getDialogSettings()
{
	return new tMediaStreamSinkDialogSettings( getFilename(), getSink()->getCreateData() );
}

void	CVideoCaptureDialogData::setSink( smart_ptr<MediaStreamSink> pSink )
{
	m_sinkData = CMediaStreamSinkDialogData( pSink );
}

std::wstring CVideoCaptureDialogData::getRecordedTimeString()
{
	REFERENCE_TIME recTime = m_recordedTime;
	
	if( m_bRecording && !m_bPaused )
	{
		REFERENCE_TIME now;
		m_Grabber.getCurReferenceTime( now );
		recTime += (now - m_startTime);
	}

	float t = float(recTime) / 10000000.0f;

	TCHAR buf[30];
	StringCchPrintf( buf, 30, TEXT("Recorded Time: %.1f"), t );

	return buf;
}
