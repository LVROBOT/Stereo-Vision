// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "GraphicOverlay.h"


#include "MainFrm.h"
#include ".\mainfrm.h"

using namespace _DSHOWLIB_NAMESPACE;

// The following is needed to make the filedialog work correctly.
struct static_init
{
	static_init() { CoUninitialize(); OleInitialize( 0 ); }
};

#pragma init_seg( user )
static_init sys_init;



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// Define the number for the timer we want to use for the clock displayed on the live video.
#define CLOCK_TIMER 2

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_SETFOCUS()
	ON_COMMAND(ID_SETTINGS_DEVICE, OnSettingsDevice)
	ON_COMMAND(ID_SETTINGS_IMAGE, OnSettingsImage)
	ON_COMMAND(ID_PREVIEW_START, OnPreviewStart)
	ON_COMMAND(ID_PREVIEW_STOP, OnPreviewStop)
	ON_COMMAND(ID_FILE_SAVEIMAGE, OnFileSaveimage)
	ON_COMMAND(ID_FILE_WRITEAVI, OnFileWriteavi)
	ON_UPDATE_COMMAND_UI(ID_PREVIEW_START, OnUpdatePreviewStart)
	ON_UPDATE_COMMAND_UI(ID_PREVIEW_STOP, OnUpdatePreviewStop)
	ON_UPDATE_COMMAND_UI(ID_SETTINGS_IMAGE, OnUpdateSettingsImage)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVEIMAGE, OnUpdateFileSaveimage)
	ON_UPDATE_COMMAND_UI(ID_FILE_WRITEAVI, OnUpdateFileWriteavi)
	ON_UPDATE_COMMAND_UI(ID_SETTINGS_DEVICE, OnUpdateSettingsDevice)
	ON_WM_CLOSE()
	ON_COMMAND(ID_APP_EXIT, OnAppExit)
	ON_WM_TIMER()
	ON_COMMAND(ID_BUTTONTRIGGERTOGGLE, OnButtontriggertoggle)
	ON_UPDATE_COMMAND_UI(ID_BUTTONTRIGGERTOGGLE, OnUpdateButtontriggertoggle)
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_OVERLAY_DISPLAY, OnOverlayDisplay)
	ON_UPDATE_COMMAND_UI(ID_OVERLAY_DISPLAY, OnUpdateOverlayDisplay)
	ON_COMMAND(ID_OVERLAY_SINK, OnOverlaySink)
	ON_UPDATE_COMMAND_UI(ID_OVERLAY_SINK, OnUpdateOverlaySink)
	ON_COMMAND(ID_OVERLAY_DEVICE, OnOverlayDevice)
	ON_UPDATE_COMMAND_UI(ID_OVERLAY_DEVICE, OnUpdateOverlayDevice)

	ON_BN_CLICKED(ID_BUTTON_PPDEVICE, OnOverlayDevice)
	ON_BN_CLICKED(ID_BUTTON_PPSINK, OnOverlaySink)
	ON_BN_CLICKED(ID_BUTTON_PPDISPLAY, OnOverlayDisplay)

	ON_COMMAND(ID_OVERLAYCOLORMODE_BESTFIT, OnOverlaycolormodeBESTFIT)
	ON_UPDATE_COMMAND_UI(ID_OVERLAYCOLORMODE_BESTFIT, OnUpdateOverlaycolormodeBESTFIT)
	ON_COMMAND(ID_OVERLAYCOLORMODE_GRAYSCALE, OnOverlaycolormodeGRAYSCALE)
	ON_UPDATE_COMMAND_UI(ID_OVERLAYCOLORMODE_GRAYSCALE, OnUpdateOverlaycolormodeGRAYSCALE)
	ON_COMMAND(ID_OVERLAYCOLORMODE_COLOR, OnOverlaycolormodeCOLOR)
	ON_UPDATE_COMMAND_UI(ID_OVERLAYCOLORMODE_COLOR, OnUpdateOverlaycolormodeCOLOR)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

//////////////////////////////////////////////////////////////////////////
/*! In the constructor of CMainFrame the video capture device that was used
    in a previous session and saved in the registry will be loaded. 
	The sink type will be set to RGB24.
*/
CMainFrame::CMainFrame()
	:	m_pSink( DShowLib::FrameHandlerSink::create( DShowLib::eRGB24, 5 ) ),
		m_IsStillImageValid( false )
{
	m_pSink->setSnapMode( false );
	m_Grabber.setSinkType( m_pSink );

	// Add the m_cOverlayCallback as a new listener to the grabber. The member method
	// overlayCallback of m_cOverlayCallback will be called for every frame.
	m_Grabber.addListener(&m_cOverlayCallback, DShowLib::GrabberListener::eOVERLAYCALLBACK);

	m_Grabber.addListener( this, DShowLib::GrabberListener::eFRAMEREADY );
}

CMainFrame::~CMainFrame()
{
}

//////////////////////////////////////////////////////////////////////////
/*	LoadPreviouslyUsedDevice
	
	This method is called from CDemoAppApp::InitInstance() after the CMainFrame
	window has been created. It tries to restore the video capture device that
	has been used in the last program session.
*/
void CMainFrame::LoadPreviouslyUsedDevice()
{
	// Restore Registry settings.
	BeginWaitCursor();
	
	// Get the last used video capture device from the registry.
	CString text = AfxGetApp()->GetProfileString( REG_SECTION_DEVICE, REG_DEVICE, TEXT("") );
	if( !text.IsEmpty() )
	{
		if( !m_Grabber.loadDeviceState( (LPCTSTR)text ) )
		{
			DShowLib::Error loadError = m_Grabber.getLastError();
			// Evaluate the returned error code.
			CString cErrorText;
			switch( loadError )
			{
			case DShowLib::eINVALID_PARAM_VAL:
				cErrorText = TEXT("Invalid XML format.");
				break;
			case DShowLib::eINCOMPATIBLE_VERSION:
				cErrorText = TEXT("Incompatible XML version.");
				break;
			case DShowLib::eINCOMPLETE:
				cErrorText = TEXT("Not all properties could be restored.");
				break;
			case DShowLib::eDEVICE_NOT_FOUND:
				cErrorText = TEXT("Previously used device not found.");
				break;
			}

			MessageBox(cErrorText,  _T("Restoring the video capture device"), MB_ICONINFORMATION|MB_OK|MB_DEFBUTTON1);
		}
	}

	resizeToVideoFormat();

	updateWindowTitle();

	EndWaitCursor();
}

void	CMainFrame::updateWindowTitle()
{
	// Display the current used video capture device in the window title bar.
	CString title = TEXT("Graphic Overlay Sample");

	if( m_Grabber.isDevValid() )
	{
		title += TEXT(" - ");
		title += m_Grabber.getDev().c_str();
	}

	SetWindowText( title );
}


//////////////////////////////////////////////////////////////////////////
/*!
*/
int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// Create a view to occupy the client area of the frame.
	if (!m_wndView.Create(NULL, NULL, AFX_WS_DEFAULT_VIEW,
		CRect(0, 0, 0, 0), this, AFX_IDW_PANE_FIRST, NULL))
	{
		TRACE0("Failed to create view window\n");
		return -1;
	}
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // Fail to create.
	}

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable.
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	m_Grabber.setHWND( m_wndView);

	m_Grabber.getOverlay(ePP_DEVICE)->setColorMode( OverlayBitmap::eBESTFIT );
	m_Grabber.getOverlay(ePP_SINK)->setColorMode( OverlayBitmap::eBESTFIT );
	m_Grabber.getOverlay(ePP_DISPLAY)->setColorMode( OverlayBitmap::eBESTFIT );

	m_Grabber.setOverlayBitmapPathPosition( ePP_DEVICE );
	drawOverlay( ePP_DEVICE );
	updateOverlayChecks();
	
	updateWindowTitle();

	// Setup the timer for the clock displayed in the live video.
	// The event shall occur once every second.
	SetTimer(CLOCK_TIMER,1000,NULL);

	return 0;
}

//////////////////////////////////////////////////////////////////////////
/*!
*/
BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs.

	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	cs.lpszClass = AfxRegisterWndClass(0);
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers
void CMainFrame::OnSetFocus(CWnd* pOldWnd)
{
	// Forward focus to the view window.
	m_wndView.SetFocus();
}

BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	// Let the view have first attempt at the command.
	if (m_wndView.OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
		return TRUE;

	// Otherwise, do default handling.
	return CFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}


//////////////////////////////////////////////////////////////////////////
/*! Show the device settings dialog. If a valid device has been selected, the
	name of the device will be displayed in the titel bar.
*/
void CMainFrame::OnSettingsDevice() 
{
	DShowLib::Grabber::tVidCapDevListPtr pVidCapDevList = m_Grabber.getAvailableVideoCaptureDevices();
	
	bool bMustRestart = false;
	if (!m_Grabber.isDevValid())
	{
		m_Grabber.closeDev();
	}
	else
	{
		if( m_Grabber.isLive() )
		{
			bMustRestart = true;
			OnPreviewStop();
		}
	}

	// Remove topmost flag of the sink window to keep it behind the device selection dialog
	::SetWindowPos( m_hWndSinkDisplay, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE );

	m_Grabber.showDevicePage();

	// Re-set topmost flag
	::SetWindowPos( m_hWndSinkDisplay, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE );

	m_IsStillImageValid = false;

	if( m_Grabber.isDevValid() )
	{
		// Save the new select device in the registry, so it can be opened
		// automatically at next program start.
		CString grabberState( m_Grabber.saveDeviceState().c_str() );

		// Get the last used video capture device from the registry.
		AfxGetApp()->WriteProfileString( REG_SECTION_DEVICE, REG_DEVICE, grabberState );
		
		resizeToVideoFormat();
		updateWindowTitle();

		if( bMustRestart )
		{
			OnPreviewStart();
		}
	}
}

//////////////////////////////////////////////////////////////////////////
/*! Show the image settings dialog. It displays controls to set the camera,
    video and video capture device properties.
*/
void CMainFrame::OnSettingsImage() 
{
	m_Grabber.showVCDPropertyPage( m_wndView, m_Grabber.getDev().getName() );

	// Save the new property settings of the video capture device in the registry, 
	// so are restored automatically at next program start.
	CString grabberState( m_Grabber.saveDeviceState().c_str() );

	// Get the last used video capture device from the registry.
	AfxGetApp()->WriteProfileString( REG_SECTION_DEVICE, REG_DEVICE, grabberState );
}


///////////////////////////////////////////////////////////////////////////////
/*! After starting the live video, some graphical elements should be displayed.
*/
void CMainFrame::OnPreviewStart()
{
	if ( m_Grabber.isLive() )
	{
		// This error should never happen.
		AfxMessageBox( TEXT("Grabber already in live-mode!") );
		return;
	}
	
	// Stop displaying the captured image in the view window's OnPaint event, 
	// as we will have live video in that window.
	m_wndView.showBuffer( 0 );

	if( !m_Grabber.startLive() )
	{
		AfxMessageBox( CString( m_Grabber.getLastError().c_str() ) );
	}
	else
	{
		m_IsStillImageValid = true;
	}

	// Redraw the displayed overlays.
	// This may be necessary because the overlay bitmap is erased 
	// when the color format of the overlay bitmap changes.
	if( m_Grabber.getOverlayBitmapPathPosition() & ePP_DEVICE )
	{
		drawOverlay( ePP_DEVICE	);
	}
	if( m_Grabber.getOverlayBitmapPathPosition() & ePP_SINK )
	{
		drawOverlay( ePP_SINK );
	}
	if( m_Grabber.getOverlayBitmapPathPosition() & ePP_DISPLAY )
	{
		drawOverlay( ePP_DISPLAY );
	}
}

//////////////////////////////////////////////////////////////////////////
/*! Stop the live video. Before the live video is stopped, an image is captured.
    This image will be displayed in the child view window.
*/
void CMainFrame::OnPreviewStop() 
{	
	if ( m_Grabber.isLive() )
	{
		m_wndView.showBuffer( m_pSink->getLastAcqMemBuffer() );

		if( !m_Grabber.stopLive() )
		{
			if ( m_Grabber.getLastError().isError() )
			{
				AfxMessageBox( m_Grabber.getLastError() );
			}
		}
		else
		{
			m_IsStillImageValid = true;
		}
	}
}

//////////////////////////////////////////////////////////////////////////
/*! Capture an image from the live video using snapImages() and save it to a file.
*/
void CMainFrame::OnFileSaveimage() 
{
	smart_ptr<MemBuffer> pBuffer = m_pSink->getLastAcqMemBuffer();
	if( pBuffer != 0 )
	{
		pBuffer->lock();

		CFileDialog dlg(
			false,			// SaveAs
			TEXT("bmp"),	// bitmap-files
			0,
			OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
			TEXT("Windows Bitmap-File (*.bmp)|*.bmp|All Files (*.*)|*.*||"),
			this
		);

		if( IDOK == dlg.DoModal() )
		{
			pBuffer->save( (LPCTSTR)dlg.GetPathName() );
		}

		pBuffer->unlock();
	}
}

//////////////////////////////////////////////////////////////////////////
/*! Show the AVI Write dialog.
*/
void CMainFrame::OnFileWriteavi() 
{
	::ShowWindow( m_hWndSinkDisplay, SW_HIDE );

	showVideoCaptureDialog( m_Grabber, m_pMediaStreamSinkDialogSettings, GetSafeHwnd() );

	::ShowWindow( m_hWndSinkDisplay, SW_SHOW );
}

//////////////////////////////////////////////////////////////////////////
/*! Update handlers for the toolbar buttons. The appropriate buttons are 
	enabled or disabled according to the live mode of the video capture device.
*/
void CMainFrame::OnUpdatePreviewStart(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( m_Grabber.isDevValid() && !m_Grabber.isLive() );
}

void CMainFrame::OnUpdatePreviewStop(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( m_Grabber.isLive() );
}

void CMainFrame::OnUpdateSettingsImage(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( m_Grabber.isDevValid() );
}

void CMainFrame::OnUpdateSettingsDevice(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( true );
}

void CMainFrame::OnUpdateFileSaveimage(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( m_IsStillImageValid && m_Grabber.isDevValid() );
}

void CMainFrame::OnUpdateFileWriteavi(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( m_Grabber.isDevValid() );
}


//////////////////////////////////////////////////////////////////////////
/*! OnClose and OnAppExit close the current video capture device.
*/
void CMainFrame::OnClose() 
{
	if( ::IsWindow(m_hWndSinkDisplay) )
	{
		::DestroyWindow( m_hWndSinkDisplay );
	}

	if( m_Grabber.isDevOpen() )
	{ 
		m_Grabber.closeDev();
	}
	
	CFrameWnd::OnClose();
}

void CMainFrame::OnAppExit() 
{
	if( m_Grabber.isDevOpen() )
	{
		m_Grabber.closeDev();
	}
	
	CFrameWnd::OnClose();
}

/*
	
*/
void CMainFrame::OnTimer( UINT nIDEvent )
{
	// If the current timer event is the clock timer, the time shall be displayed in
	// the live video. Therefore the member method "displayTime" is called.
	if( nIDEvent == CLOCK_TIMER )
	{
		displayTime();
	}

	CFrameWnd::OnTimer(nIDEvent);
}


///////////////////////////////////////////////////////////////////////////////
/*! Toggles whether the camera is triggered by an external signal.
*/
void CMainFrame::OnButtontriggertoggle() 
{
	bool bMustRestart = false;
	if ( m_Grabber.isLive() )
	{
		bMustRestart = true;
		m_Grabber.stopLive();
	}

	if( m_Grabber.getExternalTrigger() )
	{
		m_Grabber.setExternalTrigger(false);
	}
	else
	{
		m_Grabber.setExternalTrigger( true );
	}

	if ( bMustRestart )
	{
		m_Grabber.startLive();
	}	
}

///////////////////////////////////////////////////////////////////////////////
/*! If the current video capture device supports the external trigger, the 
    trigger button in the toolbar will be enabled.
*/
void CMainFrame::OnUpdateButtontriggertoggle(CCmdUI* pCmdUI) 
{	
	if( m_Grabber.hasExternalTrigger() && m_Grabber.isDevValid() )
	{
		pCmdUI->Enable( TRUE );
		pCmdUI->SetCheck( m_Grabber.getExternalTrigger() ? BST_CHECKED : BST_UNCHECKED );
	}
	else
	{
		pCmdUI->Enable( FALSE );
		pCmdUI->SetCheck( BST_UNCHECKED );
	}
}


///////////////////////////////////////////////////////////////////////////////
/*! Display the current time in the live image. This method shows how to use
	setFont, drawLine and drawText.
	The time is displayed in the lower right corner of the live video image.
*/
void CMainFrame::displayTime()
{
	CString szTimeString;	// The string will contain the time.
	CTime cTime = CTime::GetCurrentTime();
	SIZE  StringSize;		// Size of the rectangle that is needed by the string.
	smart_ptr<DShowLib::OverlayBitmap> ob;
	RECT TimeRect;
	// Displaying the time is only useful, if the live video is running.
	if ( m_Grabber.isLive() )
	{
		ob = m_Grabber.getOverlay();
		
		// Call beginPaint to tell the OverlayBitmap class that we start drawing and
		// will use a DC (device context) for GDI operations.
		ob->beginPaint();
		
		// Set a font that uses a non proportional charset.
		ob->setFont("Courier",14);

		// Copy the current time to the time string.
		szTimeString = cTime.Format("%H:%M:%S");

		// Get the size in pixels that is used by the time string in the overlay bitmap.
		GetTextExtentPoint32( m_Grabber.getOverlay()->getDC(),szTimeString,
								szTimeString.GetLength(), &StringSize);

		// This rectangle is used to draw a rectangle around the time.
		TimeRect.left = m_Grabber.getAcqSizeMaxX()-StringSize.cx-2;
		TimeRect.top = m_Grabber.getAcqSizeMaxY()-StringSize.cy-2;
		TimeRect.right = TimeRect.left + StringSize.cx+1 ;
		TimeRect.bottom = TimeRect.top + StringSize.cy+1 ;

		// Write the time string in the lower right corner.
		ob->drawText(RGB(255,255,255),
		 			 TimeRect.left + 1,
					 TimeRect.top + 1,
					 (LPCTSTR)szTimeString);

		// Draw a rectangle around the time string.
		ob->drawLine( RGB(255,255,255),  TimeRect.left,  TimeRect.top, TimeRect.right,  TimeRect.top);
		ob->drawLine( RGB(255,255,255), TimeRect.right,  TimeRect.top, TimeRect.right,  TimeRect.bottom);
		ob->drawLine( RGB(255,255,255), TimeRect.right,  TimeRect.bottom, TimeRect.left,  TimeRect.bottom);
		ob->drawLine( RGB(255,255,255),  TimeRect.left,  TimeRect.top, TimeRect.left,  TimeRect.bottom);

		// Call endPaint to release the DC and tell the OverlayBitmap class
		// that drawing has been finished.
		ob->endPaint();

	}
}

//////////////////////////////////////////////////////////////////////////
/*! ResizeToVideoFormat resizes the main window in a way that the video
    images fit exactly to the client area.
*/
void CMainFrame::resizeToVideoFormat()
{
	if( m_Grabber.isDevValid() )
	{
		CRect MainRect, ViewRect;
		GetWindowRect(MainRect);
		m_wndView.GetWindowRect(ViewRect);

		int DiffX = MainRect.Width() - ViewRect.Width();
		int DiffY = MainRect.Height() - ViewRect.Height();

		// Don't let the window size shrink too much
		int ImageX = max( m_Grabber.getAcqSizeMaxX(), 510 );
		int ImageY = max( m_Grabber.getAcqSizeMaxY(), 200 );
		
		if( ImageX > 0 && ImageY > 0 )
			SetWindowPos( &wndTop, 
						  MainRect.TopLeft().x, 
						  MainRect.TopLeft().y, 
						  ImageX+DiffX+4, 
						  ImageY+DiffY+4, 
						  SWP_FRAMECHANGED );
	}	
}


///////////////////////////////////////////////////////////////////////////////
/*! This function controls whether the overlay is visible on the live display and/or
	the grabbed images, or is completely disabled.

	To change the overlay path position, live video has to be stopped.
*/
void CMainFrame::toggleOverlayAtPosition( DShowLib::tPathPosition pos )
{
	bool bLive = m_Grabber.isLive();
	OnPreviewStop();

	DWORD oldPos = m_Grabber.getOverlayBitmapPathPosition();
	m_Grabber.setOverlayBitmapPathPosition( oldPos ^ pos );

	if( bLive )
	{
		OnPreviewStart();
	}
}

///////////////////////////////////////////////////////////////////////////////
/*! Overlay path position message handlers and UI update functions
*/
void CMainFrame::OnOverlayDisplay()
{
	toggleOverlayAtPosition( ePP_DISPLAY );
}

void CMainFrame::OnUpdateOverlayDisplay(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck( (m_Grabber.getOverlayBitmapPathPosition() & ePP_DISPLAY) ? BST_CHECKED : BST_UNCHECKED );
}

void CMainFrame::OnOverlaySink()
{
	toggleOverlayAtPosition( ePP_SINK );

	if( m_Grabber.getOverlayBitmapPathPosition() & ePP_SINK )
	{
		// Create the window object
		m_hWndSinkDisplay = ::CreateWindow(
			AfxRegisterWndClass( 0, 0, (HBRUSH)GetStockObject(BLACK_BRUSH)),
			TEXT("Sink Display"),
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT, CW_USEDEFAULT,
			CW_USEDEFAULT, CW_USEDEFAULT,
			*this,
			NULL, NULL,
			NULL );

		::ShowWindow( m_hWndSinkDisplay, SW_SHOW );

		FrameTypeInfo fti;
		if( m_pSink->getOutputFrameType( fti ) )
		{
			::SetWindowPos( m_hWndSinkDisplay, HWND_TOPMOST, 0, 0, fti.dim.cx, fti.dim.cy, SWP_NOMOVE );
		}
		else
		{
			::SetWindowPos( m_hWndSinkDisplay, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE );
		}
	}
	else
	{
		::DestroyWindow( m_hWndSinkDisplay );
	}
}

void CMainFrame::OnUpdateOverlaySink(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck( (m_Grabber.getOverlayBitmapPathPosition() & ePP_SINK) ? BST_CHECKED : BST_UNCHECKED );
}

void CMainFrame::OnOverlayDevice()
{
	toggleOverlayAtPosition( ePP_DEVICE );
}

void CMainFrame::OnUpdateOverlayDevice(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck( (m_Grabber.getOverlayBitmapPathPosition() & ePP_DEVICE) ? BST_CHECKED : BST_UNCHECKED );
}

void CMainFrame::updateOverlayChecks()
{
}

void CMainFrame::drawOverlay( DShowLib::tPathPosition pos )
{
	smart_ptr<OverlayBitmap> ob = m_Grabber.getOverlay(pos);

	ob->setEnable(true);
	ob->setFont("Courier",14);	
	ob->drawText( RGB(255,0,0),  0, 0, "IC Imaging Control 3.2" );	

	switch( pos )
	{
	case ePP_DEVICE:
		ob->drawText( RGB(0,255,0),  20, 20,  "Device Overlay Active" );
		return;
	case ePP_SINK:
		ob->drawText( RGB(0,255,0),  20, 40,  "Sink Overlay Active" );
		return;
	case ePP_DISPLAY:
		ob->drawText( RGB(0,255,0),  20, 60,  "Display Overlay Active" );
		return;
	}
}

void	CMainFrame::frameReady( DShowLib::Grabber& caller, smart_ptr<DShowLib::MemBuffer> pBuffer, DWORD FrameNumber )
{
	if( ::IsWindow( m_hWndSinkDisplay ) )
	{
		HDC hDC = ::GetDC( m_hWndSinkDisplay );
		if( hDC )
		{
			smart_ptr<BITMAPINFOHEADER> pBmInfHdr = pBuffer->getBitmapInfoHeader();

			int nLines = ::SetDIBitsToDevice( 
					hDC,					// Handle to the device
					0, 
					0, 
					pBmInfHdr->biWidth,	// Source rectangle width
					abs(pBmInfHdr->biHeight), // Source rectangle height
					0,				// X-coordinate of lower-left corner of the source rect
					0,				// Y-coordinate of lower-left corner of the source rect
					0,				// First scan line in array
					abs(pBmInfHdr->biHeight), // Number of scan lines
					pBuffer->getPtr(),	// Modified address of array with DIB bits
					reinterpret_cast<LPBITMAPINFO>( pBmInfHdr.get() ),	// Address of structure with bitmap info
					DIB_RGB_COLORS	// RGB or palette indices
				);

			::ReleaseDC( m_hWndSinkDisplay, hDC );
		}
	}
}

void CMainFrame::setOverlayBitmapColorMode( DShowLib::OverlayBitmap::tOVBColorMode mode )
{
	bool bLive = m_Grabber.isLive();
	OnPreviewStop();

	m_Grabber.getOverlay(ePP_DEVICE)->setColorMode(mode);
	m_Grabber.getOverlay(ePP_SINK)->setColorMode(mode);
	m_Grabber.getOverlay(ePP_DISPLAY)->setColorMode(mode);

	if( bLive )
	{
		OnPreviewStart();
	}
}

void CMainFrame::OnOverlaycolormodeBESTFIT()
{
	setOverlayBitmapColorMode( OverlayBitmap::eBESTFIT );
}

void CMainFrame::OnUpdateOverlaycolormodeBESTFIT(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck( m_Grabber.getOverlay(ePP_DISPLAY)->getColorMode() == OverlayBitmap::eBESTFIT );
}

void CMainFrame::OnOverlaycolormodeGRAYSCALE()
{
	setOverlayBitmapColorMode( OverlayBitmap::eGRAYSCALE );
}

void CMainFrame::OnUpdateOverlaycolormodeGRAYSCALE(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck( m_Grabber.getOverlay(ePP_DISPLAY)->getColorMode() == OverlayBitmap::eGRAYSCALE );
}

void CMainFrame::OnOverlaycolormodeCOLOR()
{
	setOverlayBitmapColorMode( OverlayBitmap::eCOLOR );
}

void CMainFrame::OnUpdateOverlaycolormodeCOLOR(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck( m_Grabber.getOverlay(ePP_DISPLAY)->getColorMode() == OverlayBitmap::eCOLOR );
}

