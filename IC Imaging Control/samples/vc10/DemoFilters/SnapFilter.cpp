
#include "stdafx.h"
#include "SnapFilter.h"

extern HINSTANCE g_hInst;

using namespace DShowLib;

CSnapFilter::CSnapFilter()
	:	m_bLiveVideoRunning( false ),
		m_bDoSnap( false ),
		m_hEvent( 0 )
{
	addStringParam( "save", &CSnapFilter::dummyGetSave, &CSnapFilter::doSave );
	addBoolParam( "snap", &CSnapFilter::dummyGetSnap, &CSnapFilter::doSnap );
}


//////////////////////////////////////////////////////////////////////////
/*!
*/
FilterInfo CSnapFilter::getStaticFilterInfo()
{
	static FilterInfo f = { L"Demo_Snap", L"", eFC_GENERIC };
	return f;
}

//////////////////////////////////////////////////////////////////////////
/*! The array "arr" is filled with the color formats, that are supported by
	this filter.
*/
void CSnapFilter::getSupportedInputTypes( FrameTypeInfoArray& arr ) const 
{
	arr.addFrameType( eRGB24 );
	arr.addFrameType( eRGB8 );
	arr.addFrameType( eY800 );
}

//////////////////////////////////////////////////////////////////////////
/*! ...
*/
bool CSnapFilter::updateInPlace( IFrame& frame )
{
	if( m_bDoSnap )
	{
		m_pBuffer = new CFrameImpl( frame );

		m_bDoSnap = false;		
		::SetEvent( m_hEvent );
	}
	return true;
}

tFilterError	CSnapFilter::doSnap( bool bSnap )
{
	tFilterError rval = eNO_ERROR;

	if( !m_bLiveVideoRunning )
	{
		rval = eINVALID_FILTER_STATE;
	}
	else
	{
		m_hEvent = ::CreateEvent( NULL, FALSE, FALSE, NULL );

		m_bDoSnap = true;

		if( ::WaitForSingleObject(m_hEvent, 500 /* ms time-out */ ) == WAIT_TIMEOUT )
		{
			rval = eINVALID_FILTER_STATE;
		}
		::CloseHandle( m_hEvent );
		m_hEvent = 0;
	}
	return rval;
}

tFilterError	CSnapFilter::dummyGetSnap( bool& bSnap )
{
	return eINVALID_FILTER_STATE;
}

tFilterError CSnapFilter::doSave( _bstr_t filename )
{
	if( m_pBuffer == 0 )
		return eINVALID_FILTER_STATE;

	saveToFileBMP( *m_pBuffer, filename );

	return eNO_ERROR;
}

tFilterError CSnapFilter::dummyGetSave( _bstr_t &Value )
{
	return eINVALID_FILTER_STATE;
}

void CSnapFilter::notifyStart(const FrameTypeInfo& in_type)
{
	m_bLiveVideoRunning = true;
}

void CSnapFilter::notifyStop(void)
{
	m_bLiveVideoRunning = false;
}

bool	CSnapFilter::hasDialog() const
{
	return true;
}

bool	CSnapFilter::callDialog( HWND hParent )
{
	if( doSnap( true ) != eNO_ERROR )
		return false;

	OPENFILENAMEW ofn;
	ZeroMemory( &ofn, sizeof( ofn ) );
	ofn.lStructSize = sizeof(ofn);

	ofn.hwndOwner = hParent;
	ofn.hInstance = g_hInst;
	ofn.lpstrFilter = L"Image Files (*.bmp)\0*.bmp\0\0";

	wchar_t filename[MAX_PATH];
	ZeroMemory( filename, sizeof(filename) );
	ofn.lpstrFile = filename;
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrDefExt = L"bmp";
	ofn.Flags = OFN_ENABLESIZING|OFN_EXPLORER|OFN_OVERWRITEPROMPT;

	if( ::GetSaveFileNameW( &ofn ) )
	{	
		doSave( filename );
		return true;
	}
	else
	{
		return false;
	}
}
