// BinarizationDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Binarization.h"
#include "BinarizationDlg.h"
#include ".\binarizationdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace DShowLib;

// CBinarizationDlg dialog



CBinarizationDlg::CBinarizationDlg(CWnd* pParent /*=NULL*/)
	:	CDialog(CBinarizationDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBinarizationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BINARIZE_ENABLE, m_BinarizeEnable);
	DDX_Control(pDX, IDC_THRESHOLD_SLIDER, m_BinarizeThreshold);
	DDX_Control(pDX, IDC_THRESHOLD_VALUE, m_BinarizeThresholdStatic);
}

BEGIN_MESSAGE_MAP(CBinarizationDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_DEVICE, OnBnClickedDevice)
	ON_BN_CLICKED(IDC_PROPERTIES, OnBnClickedProperties)
	ON_WM_SIZE()
	ON_WM_GETMINMAXINFO()
	ON_BN_CLICKED(IDC_BINARIZE_ENABLE, OnBnClickedBinarizeEnable)
	ON_WM_HSCROLL()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_CLOSE, OnBnClickedClose)
END_MESSAGE_MAP()


// CBinarizationDlg message handlers

BOOL CBinarizationDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// Setup the controls with the default values of the binarization filter
	m_BinarizeThreshold.SetRange( 0, 255 );
	m_BinarizeThreshold.SetPos( 127 );
	m_BinarizeThreshold.EnableWindow( FALSE );
	m_BinarizeThresholdStatic.SetWindowText( L"127" );
	m_BinarizeThresholdStatic.EnableWindow( FALSE );
	m_BinarizeEnable.SetCheck( BST_UNCHECKED );

	// Set the live video output window
	m_Grabber.setHWND( GetDlgItem( IDC_DISPLAY )->GetSafeHwnd() );

	// Disable overlay bitmap
	m_Grabber.setOverlayBitmapPathPosition( ePP_NONE );

	// Set the binarization filter as device frame filter
	m_Grabber.setDeviceFrameFilters( &m_binarizationFilter );

	// Show device settings dialog
	m_Grabber.showDevicePage( GetSafeHwnd() );

	// If a device was selected, start live mode.
	if( m_Grabber.isDevValid() )
	{
		m_Grabber.startLive();
	}

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.
void CBinarizationDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

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

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CBinarizationDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

/*
 *	The user clicked the "Device..."-button
 */
void CBinarizationDlg::OnBnClickedDevice()
{
	// Live mode has to be stopped before showing the device page.
	if( m_Grabber.isLive() )
		m_Grabber.stopLive();

	m_Grabber.showDevicePage( m_hWnd );

	// Start live mode again, if possible.
	if( m_Grabber.isDevValid() )
		m_Grabber.startLive();
}

/*
 *	The user clicked the "Properties..."-button
 */
void CBinarizationDlg::OnBnClickedProperties()
{
	// Show the VCD Property page
	m_Grabber.showVCDPropertyPage( GetSafeHwnd() );
}

/*
 *	Helper function for OnSize to make sure all dialog controls
 *	Are properly arranged.
 *
 *	Places the control with the ID ctrlID dist pixels away from the right border
 *	of the dialog.
 */
void CBinarizationDlg::alignRight( UINT ctrlID, int width, int dist )
{
	CWnd* pWnd = GetDlgItem( ctrlID );
	if( pWnd )
	{
		CRect rect;
		pWnd->GetWindowRect( rect );
		ScreenToClient( rect );

		pWnd->MoveWindow( width-rect.Width()-dist, rect.top, rect.Width(), rect.Height() );
	}
}

/*
 *	Helper function for OnSize to make sure all dialog controls
 *	Are properly arranged.
 *
 *	Places the control with the ID ctrlID dist pixels away from the bottom border
 *	of the dialog.
 */
void CBinarizationDlg::alignBottom( UINT ctrlID, int height, int dist )
{
	CWnd* pWnd = GetDlgItem( ctrlID );
	if( pWnd )
	{
		CRect rect;
		pWnd->GetWindowRect( rect );
		ScreenToClient( rect );

		pWnd->MoveWindow( rect.left, height-rect.Height()-dist, rect.Width(), rect.Height() );
	}
}

/*
 *	When the dialog window is resized, adjust the size of the live video window
 *	and move the controls to positions depending on the new window size.
 */
void CBinarizationDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	CWnd* pDisplay = GetDlgItem( IDC_DISPLAY );
	if( pDisplay )
	{
		CRect displayRect;
		pDisplay->GetWindowRect( displayRect );
		ScreenToClient( displayRect );

		pDisplay->MoveWindow( displayRect.left, displayRect.top, cx-displayRect.left-100, cy-displayRect.top-40 );
	}
	
	alignRight( IDC_DEVICE, cx, 10 );
	alignRight( IDC_PROPERTIES, cx, 10 );
	alignRight( IDC_CLOSE, cx, 10 );

	alignBottom( IDC_BINARIZE_STATIC, cy, 10 );
	alignBottom( IDC_BINARIZE_ENABLE, cy, 10 );
	alignBottom( IDC_THRESHOLD_STATIC, cy, 10 );
	alignBottom( IDC_THRESHOLD_SLIDER, cy, 10 );
	alignBottom( IDC_THRESHOLD_VALUE, cy, 10 );
}

/*
 *	Set the minimum window size so that all controls are always visible.
 */
void CBinarizationDlg::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	lpMMI->ptMinTrackSize = CPoint( 433, 190 );

	CDialog::OnGetMinMaxInfo(lpMMI);
}

/*
 *	The user clicked the "Enable" check box.
 *
 *	Toggle binarization at the binarization filter,
 *	and adjust the enabled state of the threshold slider.
 */
void CBinarizationDlg::OnBnClickedBinarizeEnable()
{
	// Read current checked state
	bool bEnable = m_BinarizeEnable.GetCheck() == BST_CHECKED;

	// Enclose frame filter parameter access into beginParamTransfer/endParamTransfer,
	// to get consistent values.
	m_binarizationFilter.beginParamTransfer();
	m_binarizationFilter.enable( bEnable );
	m_binarizationFilter.endParamTransfer();

	// Set threshold slider availability
	m_BinarizeThreshold.EnableWindow( bEnable );
	m_BinarizeThresholdStatic.EnableWindow( bEnable );
}

/*
 *	The user changed the position of the threshold slider.
 *
 *	Read the new value, and set it at the binarization filter.
 *	Display the value in the threshold static control.
 */
void CBinarizationDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// Read current slider position
	int th = m_BinarizeThreshold.GetPos();

	// Enclose frame filter parameter access into beginParamTransfer/endParamTransfer,
	// to get consistent values.
	m_binarizationFilter.beginParamTransfer();
	m_binarizationFilter.setThreshold( th );
	m_binarizationFilter.endParamTransfer();

	// Display the threshold in the static window.
	wchar_t buf[20];
#if _MSC_VER >= 1400
	_itow_s( th, buf, 10 ) ;
#else
	_itow( th, buf, 10 );    
#endif
	m_BinarizeThresholdStatic.SetWindowText( buf );

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

/*
 *	Stop live mode when the dialog is closed.
 */
void CBinarizationDlg::OnClose()
{
	m_Grabber.stopLive();

	CDialog::OnClose();
}

/*
 *	Stop live mode when the "close" button is pressed.
 */
void CBinarizationDlg::OnBnClickedClose()
{
	m_Grabber.stopLive();

	EndDialog( IDOK );
}
