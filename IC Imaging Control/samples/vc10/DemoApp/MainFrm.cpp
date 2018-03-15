// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "DemoApp.h"


#include "MainFrm.h"
#include "../Dialogs/Dialogs.h"

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
	ON_COMMAND(ID_BUTTONTRIGGERTOGGLE, OnButtontriggertoggle)
	ON_UPDATE_COMMAND_UI(ID_BUTTONTRIGGERTOGGLE, OnUpdateButtontriggertoggle)
	//}}AFX_MSG_MAP
	ON_WM_DESTROY()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

//////////////////////////////////////////////////////////////////////////
CMainFrame::CMainFrame()
	:	m_pSink( DShowLib::FrameHandlerSink::create( DShowLib::eRGB24, 5 ) ),
		m_IsStillImageValid( false )
{
	m_pSink->setSnapMode( true );
	m_Grabber.setSinkType( m_pSink );
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
	if( text != "" )
	{
		if( !m_Grabber.loadDeviceState( (LPCTSTR)text ) )
		{
			DShowLib::Error loadError = m_Grabber.getLastError();
			// Evaluate the returned error code.
			CString cErrorText;
			switch( loadError.getVal() )
			{
				case DShowLib::eINVALID_PARAM_VAL : cErrorText = "Invalid XML format.";
													break;
				case DShowLib::eINCOMPATIBLE_VERSION  : cErrorText = "Incompatible XML version.";
													break;
				case DShowLib::eINCOMPLETE   : cErrorText = "Not all properties could be restord.";
													break;
				case DShowLib::eDEVICE_NOT_FOUND : cErrorText = "Previously used device not found.";
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
	CString title = TEXT("DemoApp");

	if( m_Grabber.isDevValid() )
	{
		title += TEXT(" - ");
		title += m_Grabber.getDev().toString().c_str(); 
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
	
	updateWindowTitle();

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
// CMainFrame message handlers:

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
	name of the device will be displayed in the title bar.
*/
void CMainFrame::OnSettingsDevice() 
{
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
			m_Grabber.stopLive();
		}
	}

	m_Grabber.showDevicePage();

	m_IsStillImageValid = false;

	if( m_Grabber.isDevValid() )
	{
		// Save the new select device in the registry, so it can be opened
		// automatically at next program start.
		CString cGrabberState = m_Grabber.saveDeviceStateW().c_str();

		// Write the device to the registry
		AfxGetApp()->WriteProfileString( REG_SECTION_DEVICE, REG_DEVICE, cGrabberState );
		
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
	CString cGrabberState = m_Grabber.saveDeviceStateW().c_str();

	// Get the last used video capture device from the registry.
	AfxGetApp()->WriteProfileString( REG_SECTION_DEVICE, REG_DEVICE, cGrabberState );
}

//////////////////////////////////////////////////////////////////////////
/*! Start the live video.
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

	m_Grabber.startLive();

	if ( m_Grabber.getLastError().isError() )
	{
		AfxMessageBox( m_Grabber.getLastError().toStringW().c_str() );
	}
	else
	{
		m_IsStillImageValid = true;
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
		m_pSink->snapImages( 1, 2000 );

		if ( m_Grabber.getLastError().isError() )
		{
			AfxMessageBox( m_Grabber.getLastError().toStringW().c_str() );
		}
		else
		{
			m_wndView.showBuffer( m_pSink->getLastAcqMemBuffer() );
		}

		if ( ! m_Grabber.stopLive() )
		{
			if ( m_Grabber.getLastError().isError() )
			{
				AfxMessageBox( m_Grabber.getLastError().toStringW().c_str() );
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
	if( m_Grabber.isLive() )
	{
		Error e = m_pSink->snapImages( 1, 2000 );
		if ( e.isError() )
		{
			AfxMessageBox( e.toStringW().c_str() );
			return;
		}
	}

	CFileDialog dlg(
		false,			// SaveAs
		TEXT("bmp"),			// bitmap-files
		0,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		TEXT("Windows Bitmap-File (*.bmp)|*.bmp|All Files (*.*)|*.*||"),
		this
	);

	if( IDOK == dlg.DoModal() )
	{
        saveToFileBMP( *m_pSink->getLastAcqMemBuffer(), (LPCTSTR)dlg.GetPathName() );
	}
}

//////////////////////////////////////////////////////////////////////////
/*! Show the AVI Write dialog.
*/
void CMainFrame::OnFileWriteavi() 
{
	showVideoCaptureDialog( m_Grabber, GetSafeHwnd() );
}

//////////////////////////////////////////////////////////////////////////
/*! Update handlers for the toolbar buttons. The appropriate buttons are 
	enabled or disabled according to the live mode of the video capture device.
*/
void CMainFrame::OnUpdatePreviewStart(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( m_Grabber.isDevValid() && ! m_Grabber.isLive() );
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
		pCmdUI->Enable(true);
		pCmdUI->SetCheck(m_Grabber.getExternalTrigger());
	}
	else
	{
		pCmdUI->Enable(false);
		pCmdUI->SetCheck(0);
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
		int ImageX = max( m_Grabber.getAcqSizeMaxX(), 200 );
		int ImageY = max( m_Grabber.getAcqSizeMaxY(), 150 );
		
		if( ImageX > 0 && ImageY > 0 )
			SetWindowPos( &wndTop, 
						  MainRect.TopLeft().x, 
						  MainRect.TopLeft().y, 
						  ImageX+DiffX+4, 
						  ImageY+DiffY+4, 
						  SWP_FRAMECHANGED );
	}	
}

