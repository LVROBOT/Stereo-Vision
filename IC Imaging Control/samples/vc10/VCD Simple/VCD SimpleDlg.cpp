// VCD SimpleDlg.cpp : implementation file
//

#include "stdafx.h"
#include "VCD Simple.h"
#include "VCD SimpleDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVCDSimpleDlg dialog

CVCDSimpleDlg::CVCDSimpleDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CVCDSimpleDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CVCDSimpleDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CVCDSimpleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CVCDSimpleDlg)
	DDX_Control(pDX, IDC_BRIGHTNESS_CHECK, m_BrightnessAutoCheck);
	DDX_Control(pDX, IDC_BRIGHTNESS_SLIDER, m_BrightnessSlider);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CVCDSimpleDlg, CDialog)
	//{{AFX_MSG_MAP(CVCDSimpleDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SELECT_DEVICE, OnSelectDevice)
	ON_BN_CLICKED(IDC_BRIGHTNESS_CHECK, OnBrightnessCheck)
	ON_WM_HSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVCDSimpleDlg message handlers

using namespace DShowLib;

BOOL CVCDSimpleDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	InitPropertyControls();

	m_Grabber.setHWND( GetDlgItem(IDC_DISPLAY)->GetSafeHwnd() );
	m_Grabber.startLive();
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CVCDSimpleDlg::OnPaint() 
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
HCURSOR CVCDSimpleDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


//////////////////////////////////////////////////////////////////////////
/*! Let the user select a device and make initial settings
*/
bool CVCDSimpleDlg::selectDevice()
{
	m_Grabber.showDevicePage( m_hWnd );

	return m_Grabber.isDevValid();
}

/**
 * Tries to get the range interface to brightness value and the switch interface to brightness auto.
 */
void CVCDSimpleDlg::InitPropertyControls()
{
	m_pBrightnessRange = 0;
	m_pBrightnessAuto = 0;

	// Retrieve the collection of VCD Property items for the current device
		tIVCDPropertyItemsPtr pItems = m_Grabber.getAvailableVCDProperties();
	if( pItems != 0 )
	{
		// Try to find the brightness item
		tIVCDPropertyItemPtr pBrightnessItem = pItems->findItem( VCDID_Brightness );
				if( pBrightnessItem != 0 )
		{
			// Try to find the value and auto elements
						tIVCDPropertyElementPtr pBrightnessValueElement = pBrightnessItem->findElement( VCDElement_Value );
			tIVCDPropertyElementPtr pBrightnessAutoElement =  pBrightnessItem->findElement( VCDElement_Auto );

			// If a value element exists, try to acquire a range interface
			if( pBrightnessValueElement != 0 )
			{
				pBrightnessValueElement->getInterfacePtr( m_pBrightnessRange );
			}

			// If an auto element exists, try to acquire a switch interface
			if( pBrightnessAutoElement != 0 )
			{
				pBrightnessAutoElement->getInterfacePtr( m_pBrightnessAuto );

				// If successful, disable automation
				if( m_pBrightnessAuto != 0 )
					m_pBrightnessAuto->setSwitch( false );
			}
					}
	}

	// Update the slider and the checkbox
	UpdateControls();
}

void CVCDSimpleDlg::UpdateControls()
{
		// Check whether we were able to acquire a range interface to brightness value
	if( m_pBrightnessRange != 0 )
	{
		m_BrightnessSlider.EnableWindow();

		// Set the slider range
		int delta = m_pBrightnessRange->getDelta();
		m_BrightnessSlider.SetRangeMin( m_pBrightnessRange->getRangeMin() / delta );
		m_BrightnessSlider.SetRangeMax( m_pBrightnessRange->getRangeMax() / delta );

		// Set the slider position
		m_BrightnessSlider.SetPos( m_pBrightnessRange->getValue() / delta );
	}
	else
	{
		m_BrightnessSlider.EnableWindow( FALSE );
	}

	// Check whether we were able to acquire a switch interface to brightness auto
	if( m_pBrightnessAuto != 0 )
	{
		m_BrightnessAutoCheck.EnableWindow();

		m_BrightnessAutoCheck.SetCheck( m_pBrightnessAuto->getSwitch() );
	}
	else
	{
		m_BrightnessAutoCheck.EnableWindow( FALSE );
	}
	}

/**
 *	Select device button handler
 *	stops live mode, lets the user select a new device and starts live mode again.
 */
void CVCDSimpleDlg::OnSelectDevice() 
{
	// Stop live mode
	m_Grabber.stopLive();

	m_Grabber.showDevicePage( GetSafeHwnd() );
	
	if( m_Grabber.isDevValid() )
	{
		m_Grabber.startLive();
	}

	// (Re-)initialize the controls
	InitPropertyControls();
}

/**
 *	Auto check box handler
 *	Sets the brightness automation to the state of the checkbox
 */
void CVCDSimpleDlg::OnBrightnessCheck() 
{
		if( m_BrightnessAutoCheck.GetCheck() )
	{
		m_BrightnessSlider.EnableWindow( FALSE );
		m_pBrightnessAuto->setSwitch( true );
	}
	else
	{
		m_BrightnessSlider.EnableWindow();
		m_pBrightnessAuto->setSwitch( false );
	}
	}

/**
 *	Scroll handler
 *	Sets the slider value to the range interface
 */
void CVCDSimpleDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
		int delta = m_pBrightnessRange->getDelta();
	m_pBrightnessRange->setValue( m_BrightnessSlider.GetPos() * delta );
		
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}
