// MakingDeviceSettingsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MakingDeviceSettings.h"
#include "MakingDeviceSettingsDlg.h"
#include "DeviceDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMakingDeviceSettingsDlg dialog

CMakingDeviceSettingsDlg::CMakingDeviceSettingsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMakingDeviceSettingsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMakingDeviceSettingsDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMakingDeviceSettingsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMakingDeviceSettingsDlg)
	DDX_Control(pDX, IDC_PICTURE, m_staticPicture);
	DDX_Control(pDX, IDC_BTN_STOPLIVE, m_btnStopLive);
	DDX_Control(pDX, IDC_BTN_STARTLIVE, m_btnStartLive);
	DDX_Control(pDX, IDC_BTN_DEVICE, m_btnDevice);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMakingDeviceSettingsDlg, CDialog)
	//{{AFX_MSG_MAP(CMakingDeviceSettingsDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_STARTLIVE, OnBtnStartlive)
	ON_BN_CLICKED(IDC_BTN_STOPLIVE, OnBtnStoplive)
	ON_BN_CLICKED(IDC_BTN_DEVICE, OnBtnDevice)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMakingDeviceSettingsDlg message handlers

BOOL CMakingDeviceSettingsDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	m_Grabber.setHWND( GetDlgItem( IDC_PICTURE )->m_hWnd );

	m_btnStartLive.EnableWindow( false );
	m_btnStopLive.EnableWindow( false );


	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMakingDeviceSettingsDlg::OnPaint() 
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
HCURSOR CMakingDeviceSettingsDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CMakingDeviceSettingsDlg::OnBtnStartlive() 
{
	m_Grabber.startLive( true );
	m_btnStartLive.EnableWindow( false );
	m_btnStopLive.EnableWindow( true );
}

void CMakingDeviceSettingsDlg::OnBtnStoplive() 
{
	m_Grabber.stopLive();
	m_btnStartLive.EnableWindow( true );
	m_btnStopLive.EnableWindow( false );

}

void CMakingDeviceSettingsDlg::OnBtnDevice() 
{
		CDeviceDlg dlg( &m_Grabber, this );

	// Call the dialog
	if( dlg.DoModal() == -1 )
	{
		AfxMessageBox( TEXT("The dialog could not be created") );
		return;
	}
	
	if( m_Grabber.isDevValid() )
	{
		if( !m_Grabber.isLive() )
		{
			m_btnStartLive.EnableWindow( true );
		}
		else
		{
			m_btnStartLive.EnableWindow( false );
		}
	}
	else
	{
		m_btnStartLive.EnableWindow( false );
	}
}
