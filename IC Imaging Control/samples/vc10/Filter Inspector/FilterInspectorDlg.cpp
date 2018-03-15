// FilterListerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FilterInspector.h"
#include "FilterInspectorDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace DShowLib;

// CFilterInspectorDlg dialog


CFilterInspectorDlg::CFilterInspectorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFilterInspectorDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFilterInspectorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CFilterInspectorDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_DEVICE, OnBnClickedDevice)
	ON_BN_CLICKED(IDC_PROPERTIES, OnBnClickedProperties)
	ON_LBN_SELCHANGE(IDC_FILES, OnLbnSelchangeFiles)
	ON_LBN_SELCHANGE(IDC_FILTERS, OnLbnSelchangeFilters)
	ON_WM_GETMINMAXINFO()
	ON_WM_SIZE()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_DIALOG, OnBnClickedDialog)
	ON_BN_CLICKED(IDC_STARTLIVE, Startlive)
	ON_BN_CLICKED(IDC_STOPLIVE, Stoplive)
END_MESSAGE_MAP()


// CFilterInspectorDlg message handlers

BOOL CFilterInspectorDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// Set the live video output window to the static IDC_DISPLAY.
	m_Grabber.setHWND( GetDlgItem( IDC_DISPLAY )->GetSafeHwnd() );

	// Disable all overlay bitmaps.
	m_Grabber.setOverlayBitmapPathPosition( ePP_NONE );

	// Show the device page to let the user select a video capture device.
	m_Grabber.showDevicePage( m_hWnd );	

	// When a video capture device was selected, start live mode.
	if( m_Grabber.isDevValid() )
	{
		Startlive();
	}

	// Get a list with all available frame filters.
	std::vector<FilterInfo> filterInfos = FilterLoader::getAvailableFrameFilters( eFC_ALL );

	CListBox* pFilesList = (CListBox*)GetDlgItem( IDC_FILES );

	// In this loop, we create a list with all files that contain filters.
	for( size_t i = 0; i < filterInfos.size(); ++i )
	{
		// For each filter, see if its module was already added to the list.
		// If not, add it, otherwise skip it.
		bool bFound = false;
		for( size_t j = 0; j < m_FilterFileList.size(); ++j )
		{
			if( m_FilterFileList[j] == filterInfos[i].getModulePath() )
			{
				bFound = true;
				break;
			}
		}

		if( !bFound )
		{
			// Save the filter module path in a list to access it when the
			// user selects the list entry.
			m_FilterFileList.push_back( filterInfos[i].getModulePath() );

			// Add the filter file name to the list.
			pFilesList->AddString( filterInfos[i].getModuleNameW().c_str() );
		}
	}

	return TRUE;
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CFilterInspectorDlg::OnPaint() 
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
HCURSOR CFilterInspectorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

/*
 *	The user clicked the "Device..."-button
 */
void CFilterInspectorDlg::OnBnClickedDevice()
{
	// Live mode has to be stopped before showing the device page.
	if( m_Grabber.isLive() )
		Stoplive();

	m_Grabber.showDevicePage( m_hWnd );

	// Start live mode again, if possible.
	if( m_Grabber.isDevValid() )
		Startlive();
}

/*
 *	The user clicked the "Properties..."-button
 */
void CFilterInspectorDlg::OnBnClickedProperties()
{
	// Show the VCD Property page
	m_Grabber.showVCDPropertyPage( GetSafeHwnd() );
}

/*
 *	The user selected an entry in the file list.
 */
void CFilterInspectorDlg::OnLbnSelchangeFiles()
{
	CListBox* pFilesList = (CListBox*)GetDlgItem( IDC_FILES );
	CListBox* pFilterList = (CListBox*)GetDlgItem( IDC_FILTERS );

	// Get a list with all available frame filters.
	std::vector<FilterInfo> filterInfos = FilterLoader::getAvailableFrameFilters( eFC_ALL );

	// Get the index of the currently selected filter file.
	int sel = pFilesList->GetCurSel();
	if( sel != -1 )
	{
		// If a filter file was selected, fill the filter list with the filter of that file.

		// First, clear the list.
		pFilterList->ResetContent();

		// Add all filters of the selected file to the list.
		int n = 0;
		for( int i = 0; i < int(filterInfos.size()); ++i )
		{
			FilterInfo& fi = filterInfos[i];

			// Check whether the filter's module matches the selected file.
			if( m_FilterFileList[sel] == fi.getModulePath() )
			{
				pFilterList->AddString( fi.getFilterNameW().c_str() );

				// Save the index of the filter in the list of the
				// available filters in the list item's item data.
				pFilterList->SetItemData( n++, i );
			}
		}
	}
}

/*
 *	The user selected an entry in the filter list.
 */
void CFilterInspectorDlg::OnLbnSelchangeFilters()
{
	CListBox* pFilterList = (CListBox*)GetDlgItem( IDC_FILTERS );

	// Get a list with all available frame filters.
	std::vector<FilterInfo> filterInfos = FilterLoader::getAvailableFrameFilters( eFC_ALL );

	// Get the index of the currently selected filter.
	int sel = pFilterList->GetCurSel();
	if( sel != -1 )
	{
		// We previously stored the index of the filter in the list of available
		// filters in the item data of the list item. Read it back.
		int filterIndex = (int)pFilterList->GetItemData( sel );

		// Filters can only be set when live mode is stopped.
		bool bIsLive = m_Grabber.isLive();
		Stoplive();

		// Create the new filter instance.
		m_pFilter = FilterLoader::createFilter( filterInfos[filterIndex] );

		// Set the filter as device frame filter.
		m_Grabber.setDeviceFrameFilters( m_pFilter.get() );

		// Restart live mode, if possible.
		if( m_Grabber.isDevValid() && bIsLive )
		{
			Startlive();
		}

		// Enable the "Dialog..."-Button if the filter has a built-in dialog.
		GetDlgItem( IDC_DIALOG )->EnableWindow( m_pFilter->hasDialog() );
	}
}

/*
 *	Set the minimum window size so that all controls are always visible.
 */
void CFilterInspectorDlg::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	lpMMI->ptMinTrackSize = CPoint( 500, 450 );

	CDialog::OnGetMinMaxInfo(lpMMI);
}

/*
 *	When the dialog window is resized, adjust the size of the live video window.
 */
void CFilterInspectorDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
    
	CWnd* pDisplay = GetDlgItem( IDC_DISPLAY );
	if( pDisplay )
	{
		CRect displayRect;
		pDisplay->GetWindowRect( displayRect );
		ScreenToClient( displayRect );

		pDisplay->MoveWindow( displayRect.left, displayRect.top, cx-displayRect.left-11, cy-displayRect.top-11 );
	}
}

/*
 *	Stop live mode before closing the dialog
 */
void CFilterInspectorDlg::OnClose()
{
	m_Grabber.stopLive();

	CDialog::OnClose();
}

/*
 *	The user clicked the "Dialog..."-Button
 */
void CFilterInspectorDlg::OnBnClickedDialog()
{
	// Display the current filter's dialog.
	m_pFilter->callDialog( m_hWnd );
}

/*
 *	Start live mode
 */
void CFilterInspectorDlg::Startlive()
{
	// Try to start live mode
	if( !m_Grabber.startLive() )
	{
		AfxMessageBox( TEXT("Error: Live mode could not be started. The filter might require a different video format."), MB_OK|MB_ICONERROR );
	}
	else
	{
		// Update the start and stop buttons availability.
		GetDlgItem( IDC_STARTLIVE )->EnableWindow( !m_Grabber.isLive() );
		GetDlgItem( IDC_STOPLIVE )->EnableWindow( m_Grabber.isLive() );
	}
}

/*
 *	Stop live mode
 */
void CFilterInspectorDlg::Stoplive()
{
	// Stop live mode
	m_Grabber.stopLive();

	// Update the start and stop buttons availability.
	GetDlgItem( IDC_STARTLIVE )->EnableWindow( !m_Grabber.isLive() );
	GetDlgItem( IDC_STOPLIVE )->EnableWindow( m_Grabber.isLive() );
}
