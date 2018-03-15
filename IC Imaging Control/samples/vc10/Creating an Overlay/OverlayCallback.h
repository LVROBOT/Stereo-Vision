// OverlayCallback.h: interface for the COverlayCallback class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OVERLAYCALLBACK_H__4CA9A710_0366_4FDA_85C9_429524956170__INCLUDED_)
#define AFX_OVERLAYCALLBACK_H__4CA9A710_0366_4FDA_85C9_429524956170__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "tisudshl.h"
using namespace DShowLib;
class COverlayCallback : public GrabberListener  
{
public:
	COverlayCallback();
	virtual ~COverlayCallback();
	virtual void overlayCallback( Grabber& param, smart_ptr<OverlayBitmap> pBitmap, const tsMediaSampleDesc& );

private:
	int	m_displayCallCount;
};
#endif // !defined(AFX_OVERLAYCALLBACK_H__4CA9A710_0366_4FDA_85C9_429524956170__INCLUDED_)
