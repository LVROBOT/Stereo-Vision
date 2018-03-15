// DigitalIODlg.cpp : implementation file
//
// This sample deomstrates, how to use the DigitalIO of the
// Dxx 21BF04 cameras. 
//
// It uses the  CSimplePropertyAccess class out of the "../Common/SimplePropertyAccess.h"
// directory, that provides easy access to the camera's properties.
//
/////////////////////////////////////////////////////////////////////////////


#include "stdafx.h"
#include "DigitalIO.h"
#include "DigitalIODlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DigitalIODlg dialog

DigitalIODlg::DigitalIODlg(CWnd* pParent /*=NULL*/)
	: CDialog(DigitalIODlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(DigitalIODlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void DigitalIODlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DigitalIODlg)
	DDX_Control(pDX, IDC_CHECKOUTPUT, m_chkDigitalOutputState);
	DDX_Control(pDX, IDC_CHECKINPUT, m_chkDigitalInputState);
	DDX_Control(pDX, IDC_BUTTONWRITEOUTPUT, m_cButtonWriteOutput);
	DDX_Control(pDX, IDC_BUTTONREADINPUT, m_cButtonReadInput);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(DigitalIODlg, CDialog)
	//{{AFX_MSG_MAP(DigitalIODlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTONREADINPUT, OnButtonreadinput)
	ON_BN_CLICKED(IDC_BUTTONWRITEOUTPUT, OnButtonwriteoutput)
	ON_WM_HSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DigitalIODlg message handlers

using namespace DShowLib;

BOOL DigitalIODlg::OnInitDialog()
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

void DigitalIODlg::OnPaint() 
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
HCURSOR DigitalIODlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

//////////////////////////////////////////////////////////////////////////
/*! Let the user select a device and make initial settings
*/
bool DigitalIODlg::selectDevice()
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
void DigitalIODlg::InitControls()
{
	if( m_Grabber.isDevValid())
	{
		// Initialize the VCDProp object to access the properties of our ICImagingControl
		// object
		m_VCDProp.init( m_Grabber.getAvailableVCDProperties() );
		// Check, whether DigitalIO is supported by the currently used video capture device.
		if( m_VCDProp.isAvailable(VCDID_GPIO) )
		{
			// Digital Input
			m_cButtonReadInput.EnableWindow();
			// Read the current state of the input.
			OnButtonreadinput();

			// Digital Output
			m_cButtonWriteOutput.EnableWindow();
			m_chkDigitalOutputState.EnableWindow();

			// Set the check box's value to the current state of the input
			m_chkDigitalOutputState.SetCheck( m_VCDProp.getValue(VCDElement_GPIOOut));
		}
		else
		{
			m_cButtonReadInput.EnableWindow(FALSE);
			m_cButtonWriteOutput.EnableWindow(FALSE);
			m_chkDigitalOutputState.EnableWindow(FALSE);
		}
	}
}


//////////////////////////////////////////////////////////////////////////
/*! Read the current state of the digital input and set the check box to this
	value.
*/
void DigitalIODlg::OnButtonreadinput() 
{
	// Query the current state of all digital inputs of the camera.
	m_VCDProp.push(VCDElement_GPIORead);

	// Set the values of the digital inputs to the related checkboxes.
	m_chkDigitalInputState.SetCheck(m_VCDProp.getValue(VCDElement_GPIOIn));
}

//////////////////////////////////////////////////////////////////////////
/*! Read the value to be set from the check box. Then send it to the camera.
*/
void DigitalIODlg::OnButtonwriteoutput() 
{
	// Set the value of the checkbox.
	m_VCDProp.setValue(VCDElement_GPIOOut,(long)m_chkDigitalOutputState.GetCheck());

	// Send the values to the camera and set the digital output state.
	m_VCDProp.push(VCDElement_GPIOWrite);
}

