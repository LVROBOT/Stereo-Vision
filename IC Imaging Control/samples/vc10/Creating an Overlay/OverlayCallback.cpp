// OverlayCallback.cpp: implementation of the COverlayCallback class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GraphicOverlay.h"
#include "OverlayCallback.h"
#include "unknwn.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

COverlayCallback::COverlayCallback()
	:	m_displayCallCount( 0 )
{
}

COverlayCallback::~COverlayCallback()
{

}

///////////////////////////////////////////////////////////////////////////////
/*! The overlayCallback method is called, after the video capture device has
	delivered a new frame. In this method drawing operations can be performed.
*/
void COverlayCallback::overlayCallback( Grabber& param, smart_ptr<OverlayBitmap> pBitmap, const tsMediaSampleDesc &MediaSample )
{
	CString szText;

	switch( pBitmap->getPathPosition() )
	{
	case ePP_DEVICE:
		szText.Format( TEXT("Device: Frame %d   "), MediaSample.FrameNumber );
		pBitmap->drawText(RGB(255,255,0), 20, 100, (LPCTSTR)szText );
		break;
	case ePP_SINK:
		szText.Format( TEXT("Sink: Frame %d   "), MediaSample.FrameNumber );
		pBitmap->drawText(RGB(255,255,0), 20, 120, (LPCTSTR)szText );
		break;
	case ePP_DISPLAY:
		szText.Format( TEXT("Display: No Frame Number Available, called %d times"), m_displayCallCount++ );
		pBitmap->drawText(RGB(255,255,0), 20, 140, (LPCTSTR)szText );
		break;
	}
}
