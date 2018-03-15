// ChildView.cpp : implementation of the CChildView class
//

#include "stdafx.h"
#include "ScrollAndZoom.h"
#include "ChildView.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChildView

CChildView::CChildView( DShowLib::Grabber* pGrabber )
	:	m_pGrabber(pGrabber ),
		m_bdonoterase( false )
{
}

//////////////////////////////////////////////////////////////////////////
/*!
*/
CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView,CWnd )
	//{{AFX_MSG_MAP(CChildView)
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_VSCROLL()
	ON_WM_HSCROLL()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CChildView message handlers

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), HBRUSH(COLOR_WINDOW+1), NULL);

	return TRUE;
}

void CChildView::OnPaint()
{
	CPaintDC dc(this); // Device context for painting.

	PaintImage();
}

void CChildView::showBuffer( const DShowLib::Grabber::tMemBufferPtr& pBuffer )
{
	m_pBuffer = pBuffer;
}


///////////////////////////////////////////////////////////////////////////////
/*! SetupScrollBars sets the current values of the video window size and position
	and the size of this window to the scroll bars. This method has to be called,
	if the size of the video window changes, for example on zoom or on video format
	change.
*/
void CChildView::SetupScrollBars()
{
	long posx;
	long posy;
	long width;
	long height;
	RECT clientRect;	// Rectangle of the client window
	long clientEdge;    // Will contain the length of the edges
	SCROLLINFO si;		// Structure to setup the scroll bars

	ZeroMemory(&si, sizeof(SCROLLINFO) );
	si.cbSize = sizeof(si);

	if( m_pGrabber->isDevValid())
	{
		// Get the size of the client rect, that is our window.
		GetClientRect( &clientRect );

		// Retrieve the actual size and position of the Grabber's video window.
		if( m_pGrabber->getWindowPosition( posx, posy, width, height ) == true )
		{
			// Make sure that the whole client area is used.
			clientEdge = clientRect.right - clientRect.left;
			if( clientEdge > width + posx && posx < 0)
			{
				posx -= posx + width - clientEdge;
				if( posx > 0) posx = 0;
			}

			clientEdge = clientRect.bottom - clientRect.top;
			if( clientEdge > height + posy && posy < 0)
			{
				posy -= posy + height - clientEdge;
				if( posy > 0) posy = 0;
			}

			m_pGrabber->setWindowPosition(posx ,posy);

			si.fMask = SIF_PAGE|SIF_RANGE|SIF_POS;
			si.nMin  = 0;
			if( height > clientRect.bottom) // Hide the scroll bar, if the sizes are equal.
			{
				// The page size for the scroll bar is the width or height of the client window.
				si.nPage =  clientRect.bottom ;

				// The maximum scroll value is the width or height of the video window. If
				// the maximum is less than the page size, the scroll bar is hidden.
				si.nMax = height;

				// The current scroll position is the negative value of the video window's
				// position.
				si.nPos = -posy;
			}
			else
			{
				si.nMax	 = 2;
				si.nPage = si.nMax +1; // This hides the scroll bar.
			}

			// Setup the vertical scroll bar.
			SetScrollInfo( SB_VERT,&si);

			if( width > clientRect.right) // Hide the scroll bar, if the sizes are equal.
			{
				// Do the same for the horizontal scrollbar.
				si.nPage = clientRect.right;
				si.nMax =  width;
				si.nPos = -posx;
			}
			else
			{
				si.nMax	 = 2;
				si.nPage = si.nMax +1; // This hides the scrollbar.
			}
			SetScrollInfo( SB_HORZ,&si);
			PaintImage();
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
/*! The scrollbars have to resized, if the window size itself changes.
*/
void CChildView::OnSize(UINT nType, int cx, int cy)
{
	SetupScrollBars();
	CWnd ::OnSize(nType, cx, cy);
}

///////////////////////////////////////////////////////////////////////////////
/*! The OnVScroll message handler is called, if the user modifies the vertical scroll bar.
*/
void CChildView::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	OnScroll(nSBCode, nPos, SB_VERT);
}

///////////////////////////////////////////////////////////////////////////////
/*! The same has to be done for the horizontal scrollbar.
*/
void CChildView::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	OnScroll(nSBCode, nPos, SB_HORZ);
}

//////////////////////////////////////////////////////////////////////////
/*! OnScroll handles the HScroll and VScroll events.
*/
void CChildView::OnScroll(UINT nSBCode, UINT nPos, int iScrollBar)
{
	long posx;
	long posy;
	long width;
	long height;
	bool bIsScroll = false;
	SCROLLINFO si;	// Structure to setup the scroll bars.
	ZeroMemory(&si, sizeof(SCROLLINFO) );


	// Get the current size and position of the video window.
	m_pGrabber->getWindowPosition( posx, posy, width, height);

	si.cbSize = sizeof(si);
	si.fMask = SIF_POS;
	GetScrollInfo( iScrollBar, &si);

	switch( nSBCode )
	{
		case SB_LINERIGHT :	si.nPos++;
							bIsScroll = true;
							break;

		case SB_LINELEFT :  si.nPos--;
							bIsScroll = true;
							break;

		case SB_PAGERIGHT : si.nPos+=5;
							bIsScroll = true;
							break;

		case SB_PAGELEFT :  si.nPos-=5;
							bIsScroll = true;
							break;

		case SB_THUMBTRACK:
		case SB_THUMBPOSITION:	si.nPos   = nPos;
								bIsScroll = true;
								break;
	}

	// Check whether a scroll event has been sent.
	if( bIsScroll == true )
	{
		// Scroll vertically or horizontally by passing the scroll bar position
		// as parameter to setWindowPosition.
		// The scroll position of the scroll bar has to be passed as a negative
		// value to setWindowPosition.
		if( iScrollBar == SB_HORZ )
		{
			m_pGrabber->setWindowPosition(-si.nPos, posy );
		}
		else
		{
			m_pGrabber->setWindowPosition(posx ,-si.nPos);
		}

		// Very important: The new scroll position must be passed to the scroll bar.
		// If not, the scroll bar would not show the new position.
		si.fMask  = SIF_POS;
		SetScrollInfo( iScrollBar, &si, TRUE);
		OnPaint();

	}
}


//////////////////////////////////////////////////////////////////////////
/*! PaintImage() draws the last captured frame, if the live mode has been
	stopped.
*/
void CChildView::PaintImage()
{

	if( !m_pGrabber->isLive() )
	{
		CDC *dc = GetDC();
		long posx;
		long posy;
		long width;
		long height;
		CRect rect;
		float fZoomFactor;

		if( m_pBuffer != 0 )
		{
			m_bdonoterase = true;

			smart_ptr<BITMAPINFOHEADER> pInf = m_pBuffer->getBitmapInfoHeader();
			m_pGrabber->getWindowPosition( posx, posy, width, height );
			GetClientRect( &rect );

			// Compute currently used zoom factor.
			fZoomFactor = (float)width / (float)(pInf->biWidth);

			// Compute the clipping rectangle's width and height that is displayed
			// in the client area of the child view.
			width  = (long)((float)(rect.Width() ) / fZoomFactor);
			height = (long)((float)(rect.Height()) / fZoomFactor);
			posy =  height - pInf->biHeight - (long)((float)posy / fZoomFactor) ; // DIB bottom up.
			posx = (long)((float)posx / fZoomFactor);

			void* pBuf = m_pBuffer->getPtr();
			SetStretchBltMode(dc->m_hDC ,COLORONCOLOR);
			int nLines = StretchDIBits( dc->GetSafeHdc(),			// handle to the device context of the window
										0,0,
										rect.Width(),rect.Height(),
										-posx,						// x-coordinate of lower-left corner of the source rect
										-posy,						// y-coordinate of lower-left corner of the source rect
										width,
										height,
										m_pBuffer->getPtr(),		// modified address of array with DIB bits
										reinterpret_cast<LPBITMAPINFO>( &*pInf ),	// address of structure with bitmap info
										DIB_RGB_COLORS,				// RGB or palette indices
										SRCCOPY
										);
			if( nLines == GDI_ERROR )
			{
				AfxMessageBox( TEXT("GDI_ERROR") );
			}

			EraseBackground(dc);

		}
		ReleaseDC( dc );
	}
}

//////////////////////////////////////////////////////////////////////////
/*! OnEraseBackground is called by the frame work.
*/
BOOL CChildView::OnEraseBkgnd(CDC* pDC)
{
	if( m_pGrabber->isLive() || m_bdonoterase == true)
	{
		EraseBackground(pDC);
		return TRUE;
	}
	else
	{
		return CWnd ::OnEraseBkgnd(pDC);
	}
}

//////////////////////////////////////////////////////////////////////////
/*! To get flickerfree drawing when the window is resized, the size of the
    video image is compared to the size of the child view. If it is smaller,
	white rectangles are drawn on the right or bottom of the video image.
*/
void CChildView::EraseBackground(CDC *pDC)
{
	long posx;
	long posy;
	long width;
	long height;
	CRect rect;
	CRect DrawRect;
	CPen cPen(PS_SOLID,1,RGB(255,255,255));
	CBrush cBrush(RGB(255,255,255));
	CPen *pOldPen;
	CBrush *pOldBrush;

	m_pGrabber->getWindowPosition( posx, posy, width, height );
	GetClientRect( &rect );

	pOldPen   = (CPen*)pDC->SelectObject( &cPen);
	pOldBrush = (CBrush*)pDC->SelectObject( &cBrush);

	if( width + posx < rect.Width())
	{
		DrawRect.left = width + posx;
		DrawRect.right = rect.right;
		DrawRect.top = 0;
		DrawRect.bottom = rect.bottom;
		pDC->Rectangle(&DrawRect);
	}

	if( height + posy < rect.Height())
	{
		DrawRect.left = 0;
		DrawRect.right = rect.right;
		DrawRect.top = height + posy;
		DrawRect.bottom = rect.bottom;
		pDC->Rectangle(&DrawRect);
	}

	pDC->SelectObject( pOldPen);
	pDC->SelectObject( pOldBrush);
}
