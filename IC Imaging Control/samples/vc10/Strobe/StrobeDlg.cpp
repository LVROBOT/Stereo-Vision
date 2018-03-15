// StrobeDlg.cpp : implementation file
//
// This sample deomstrates, how to enable and disable the strobe of the
// Dxx 21BF04 cameras. 
//
// It uses the  CSimplePropertyAccess class out of the "../Common/SimplePropertyAccess.h"
// directory, that provides easy access to the camera's properties.
// The strobe property has the GUID "VCDID_Strobe" and is of the "switch" type. Thus the
// methods "getSwitch" and "setSwitch" are used to handle the strobe property.
//
/////////////////////////////////////////////////////////////////////////////


#include "stdafx.h"
#include "Strobe.h"
#include "StrobeDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// StrobeDlg dialog

StrobeDlg::StrobeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(StrobeDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(StrobeDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

StrobeDlg::~StrobeDlg()
{
}

void StrobeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(StrobeDlg)
	DDX_Control(pDX, IDC_CHECKSTROBE, m_chkStrobe);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(StrobeDlg, CDialog)
	//{{AFX_MSG_MAP(StrobeDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_CHECKSTROBE, OnCheckStrobe)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// StrobeDlg message handlers

using namespace DShowLib;

BOOL StrobeDlg::OnInitDialog()
{
	CDialog::OnInitDialog();


	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	DShowLib::InitLibrary();


    // Set output window for live mode
	m_Grabber.setHWND( GetDlgItem( IDC_DISPLAY )->GetSafeHwnd() );

	selectDevice();
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void StrobeDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR StrobeDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

//////////////////////////////////////////////////////////////////////////
/*! Let the user select a device and make initial settings
*/
bool StrobeDlg::selectDevice()
{
	m_Grabber.showDevicePage( m_hWnd );

	if( m_Grabber.isDevValid() )
	{
		InitControls();
	}
	// Start live mode
	m_Grabber.startLive();
	return m_Grabber.isDevValid();
}


//////////////////////////////////////////////////////////////////////////
/*! Initialze the VCDProp class with the properties, that are supported by
	the currently used video capture device.
*/
void StrobeDlg::InitControls()
{
	if( m_Grabber.isDevValid())
	{
		// Initialize the VCDProp object to access the properties of our ICImagingControl
		// object
		m_VCDProp.init( m_Grabber.getAvailableVCDProperties() );

		// Check, whether strobe is supported by the currently used video capture device.
		if( m_VCDProp.isAvailable(VCDID_Strobe))
		{
			m_chkStrobe.EnableWindow();
			// Query the current state of strobe and set the strobe check box to this state.
			// The strobe property of the Dxx 21BF04 is a "switch" interface, thus the method 
			// "getSwitch" is used.

			if(m_VCDProp.getSwitch(VCDID_Strobe) )
				m_chkStrobe.SetCheck(BST_CHECKED);
			else
				m_chkStrobe.SetCheck(BST_UNCHECKED);
		}
		else
		{
			// Strobe is not supported, so disable the strobe check box.
			m_chkStrobe.EnableWindow(FALSE);
			m_chkStrobe.SetCheck(BST_UNCHECKED); 
		}
	}
}

//////////////////////////////////////////////////////////////////////////
/*! React on a user input on the strobe checkbox. 
	Set the strobe to the value of the strobe checkbox. The strobe property 
	of the Dxx 21BF04 is a "switch" interface, thus the method "setSwitch" is
	used.
*/
void StrobeDlg::OnCheckStrobe() 
{
	if( m_Grabber.isDevValid())
	{
		m_VCDProp.setSwitch(VCDID_Strobe, m_chkStrobe.GetCheck() == BST_CHECKED);
	}
}
