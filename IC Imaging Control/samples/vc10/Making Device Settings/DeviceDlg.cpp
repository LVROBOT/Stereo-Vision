// DeviceDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MakingDeviceSettings.h"
#include "DeviceDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDeviceDlg dialog

CDeviceDlg::CDeviceDlg( Grabber* pGrabber, CWnd* pParent )
	:	CDialog(CDeviceDlg::IDD, pParent),
		m_pGrabber( pGrabber )
{
	//{{AFX_DATA_INIT(CDeviceDlg)
	//}}AFX_DATA_INIT
}


void CDeviceDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDeviceDlg)
	DDX_Control(pDX, IDC_CHECK_FLIPH, m_chkFlipH);
	DDX_Control(pDX, IDC_CHECK_FLIPV, m_chkFlipV);
	DDX_Control(pDX, IDC_STATIC_SERIAL_OUT, m_staticSerialOut);
	DDX_Control(pDX, IDC_COMBO_VIDEONORM, m_cboVideoNorm);
	DDX_Control(pDX, IDC_COMBO_VIDEOFORMAT, m_cboVideoFormat);
	DDX_Control(pDX, IDC_COMBO_INPUTCHANNEL, m_cboInputChannel);
	DDX_Control(pDX, IDC_COMBO_FRAMERATE, m_cboFrameRate);
	DDX_Control(pDX, IDC_COMBO_DEVICE, m_cboDevice);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDeviceDlg, CDialog)
	//{{AFX_MSG_MAP(CDeviceDlg)
	ON_CBN_SELCHANGE(IDC_COMBO_DEVICE, OnSelchangeComboDevice)
	ON_CBN_SELCHANGE(IDC_COMBO_FRAMERATE, OnSelchangeComboFramerate)
	ON_CBN_SELCHANGE(IDC_COMBO_INPUTCHANNEL, OnSelchangeComboInputchannel)
	ON_CBN_SELCHANGE(IDC_COMBO_VIDEOFORMAT, OnSelchangeComboVideoformat)
	ON_CBN_SELCHANGE(IDC_COMBO_VIDEONORM, OnSelchangeComboVideonorm)
	ON_BN_CLICKED(IDC_CHECK_FLIPH, OnCheckFliph)
	ON_BN_CLICKED(IDC_CHECK_FLIPV, OnCheckFlipv)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDeviceDlg message handlers

//
// OnInitDialog
//
// Checks if the live video is running. If so, a message is displayed,
// telling you that the device dialog cannot be displayed. Otherwise.
// the devices current state is saved and the controls are initialized.
//
BOOL CDeviceDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	if( m_pGrabber->isDevValid() )
	{
		if( m_pGrabber->isLive() )
		{
			// Display a message that the dialog cannot be displayed while the
			// grabber is in live mode.
			AfxMessageBox( TEXT("The device settings dialog is not available while the live video is running.\n\nStop the live video first.") );
			
			// call the click event of OK button of the super class
			CDialog::OnOK();

			return TRUE;

		}
	}
	
	// Store the state of the currently valid device.
	saveDeviceSettings();

	// Fill the device combo box with appropriate values.
	updateDevices();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


//Event Procedures

//
// OnCancel
//
// Close form and restore the device setting to
// undo all changes.
//
void CDeviceDlg::OnCancel() 
{
	restoreDeviceSettings();

	CDialog::OnCancel();
}



//
// OnSelchangeComboDevice
//
// Opens the selected device and tries to read out the serial number. 
// If the serial number could be retrieved successfully, it is displayed. 
// Otherwise "n\a" is displayed. This function also updates the other controls
//
void CDeviceDlg::OnSelchangeComboDevice() 
{
	// Open the device
	if( m_cboDevice.IsWindowEnabled() )
	{
		CString device;
		
		m_cboDevice.GetWindowText( device );
		
		if( m_pGrabber->openDev( (LPCTSTR)device ) )
		{
			__int64 iSerial;
			CString serial;

			// Try to read out the serial number
			if( m_pGrabber->getDev().getSerialNumber( iSerial ) )
			{
				// Display serial
				serial.Format( TEXT("%I64X"), iSerial );
				m_staticSerialOut.SetWindowText( serial );
			}
			else
			{
				// Display "n\a"
				m_staticSerialOut.SetWindowText( NOT_AVAILABLE );
			}

			// Update the other controls, since they depend on the current device.
			updateVideoNorms();
			updateInputChannels();
			updateFlip();
		}
	}
}


//
// OnSelchangeComboFramerate
//
// Sets the selected frame rate
//
void CDeviceDlg::OnSelchangeComboFramerate() 
{
	if( m_cboFrameRate.IsWindowEnabled() )
	{
		CString framerate;

		m_cboFrameRate.GetWindowText( framerate );
		
		// Since we retrieve a string from the combo box, but setFPS
		// needs a double value to be passed to, we use atof to typecast
		// the string.
		if( !m_pGrabber->setFPS( _wtof( framerate.GetBuffer( framerate.GetLength() ) ) ) )
		{
			AfxMessageBox( TEXT("Framerate Error") );
		}
	}
}

//
// OnSelchangeComboInputchannel
//
// Sets the selected input channel.
//
void CDeviceDlg::OnSelchangeComboInputchannel() 
{
	if( m_cboInputChannel.IsWindowEnabled() )
	{
		CString inputchannel;

		m_cboInputChannel.GetWindowText( inputchannel );
		
		if( !m_pGrabber->setInputChannel( (LPCTSTR)inputchannel ) )
		{
			AfxMessageBox( TEXT("Input Channel Error") );
		}
	}
}


//
// OnSelchangeComboVideoformat
//
// Sets the selected video format
//
void CDeviceDlg::OnSelchangeComboVideoformat() 
{
	if( m_cboVideoFormat.IsWindowEnabled() )
	{
		CString videoformat;
		m_cboVideoFormat.GetWindowText( videoformat );

		if( !m_pGrabber->setVideoFormat( (LPCTSTR)videoformat ) )
		{
			AfxMessageBox( TEXT("Video Format Error") );
		}
	}

	// Update the frame rate combo box, since the frame rates depend on the 
	// video format
    updateFrameRates();
}


//
// OnSelchangeComboVideonorm
//
// Sets the selected video norm
//
void CDeviceDlg::OnSelchangeComboVideonorm() 
{
	if( m_cboVideoNorm.IsWindowEnabled() )
	{
		CString videonorm;

		m_cboVideoNorm.GetWindowText( videonorm );
		
		if( !m_pGrabber->setVideoNorm( (LPCTSTR)videonorm ) )
		{
			AfxMessageBox( TEXT("Video Norm Error") );
		}
	}
    
	// Update the video format combo box, since the video formats depend on the 
	// video norm.
    updateVideoFormats();
}

//
// OnCheckFliph
//
// Toggles the horizontal flip.
//
void CDeviceDlg::OnCheckFliph() 
{
	if( m_pGrabber->isFlipHAvailable () )
	{
		m_pGrabber->setFlipH( m_chkFlipH.GetCheck() == 1 );
	}
}


//
// OnCheckFlipv
//
// Toggles the vertical flip.
//
void CDeviceDlg::OnCheckFlipv() 
{
	if( m_pGrabber->isFlipVAvailable () )
	{
		m_pGrabber->setFlipV( m_chkFlipV.GetCheck() == 1 );
	}	
}


/////////////////////////////////////////////////////////////////////////////
// Update Procedures


//
// updateDevices
//
// Fills the device combo box with appropriate values and selects 
// the currently valid device.
//
void CDeviceDlg::updateDevices()
{
	// Clear combo box
	m_cboDevice.ResetContent();

	// Retrieve the list of available video capture devices.
	Grabber::tVidCapDevListPtr pVidCapDevList = m_pGrabber->getAvailableVideoCaptureDevices();
	if( pVidCapDevList == 0 || pVidCapDevList->empty() )
	{
        m_cboDevice.AddString( NOT_AVAILABLE );
        m_cboDevice.EnableWindow( false );
        m_cboDevice.SetCurSel( 0 );
		return;
	}

	m_cboDevice.EnableWindow( true );

	// Fill the combo box
	for ( Grabber::tVidCapDevList::iterator it = 
		  pVidCapDevList->begin(); 
		  it != pVidCapDevList->end(); 
		  ++it )
	{
		m_cboDevice.AddString( CString( it->c_str() ) );
	}

	// Select the currently valid device
	if( m_pGrabber->isDevValid() )
	{
		m_cboDevice.SelectString( -1, CString( m_pGrabber->getDev().c_str() ) );
	}

	// Update the other controls since they depend on this one.
	updateVideoNorms();
	updateInputChannels();
	updateFlip();
}


//
// updateVideoNorms
//
// Fills the video norm combo box with appropriate values and selects 
// the currently selected video norm.
//
void CDeviceDlg::updateVideoNorms()
{
	// Clear combo box
	m_cboVideoNorm.ResetContent();

	if( m_pGrabber->isVideoNormAvailableWithCurDev() )
	{
		// Retrieve the list of available video norms.
		Grabber::tVidNrmListPtr pVidNrmList = m_pGrabber->getAvailableVideoNorms();
		if ( pVidNrmList == 0 || pVidNrmList->empty() )
		{
			m_cboVideoNorm.AddString( NOT_AVAILABLE );
			m_cboVideoNorm.EnableWindow( false );
			m_cboVideoNorm.SetCurSel( 0 );
			return;
		}

		m_cboVideoNorm.EnableWindow( true );

		// Fill the combo box
		for ( Grabber::tVidNrmList::iterator it = 
			  pVidNrmList->begin();
			  it != pVidNrmList->end();
			  ++it )
		{
			m_cboVideoNorm.AddString( CString( it->c_str() ) );
		}

		// Select the currently valid video norm.
		m_cboVideoNorm.SelectString( -1, CString( m_pGrabber->getVideoNorm().c_str() ) );
	}
	else
	{
        m_cboVideoNorm.AddString( NOT_AVAILABLE );
        m_cboVideoNorm.EnableWindow( false );
        m_cboVideoNorm.SetCurSel( 0 );
	}

	// Update the video formats since they depend on the video norm.
	updateVideoFormats();
}


//
// updateVideoFormats
//
// Fills the video format combo box with appropriate values and selects 
// the currently selected video format.
//
void CDeviceDlg::updateVideoFormats()
{
	// Clear combo box
	m_cboVideoFormat.ResetContent();

	if( m_pGrabber->isDevValid() )
	{
		// Retrieve the list of available video formats.
		Grabber::tVidFmtListPtr pVidFmtList = m_pGrabber->getAvailableVideoFormats();
		if ( pVidFmtList == 0 || pVidFmtList->empty() )
		{
			m_cboVideoFormat.AddString( NOT_AVAILABLE );
			m_cboVideoFormat.EnableWindow( false );
			m_cboVideoFormat.SetCurSel( 0 );
		}

		m_cboVideoFormat.EnableWindow( true );
		
		// Fill the combo box
		for ( Grabber::tVidFmtList::iterator it = 
			  pVidFmtList->begin(); 
			  it != pVidFmtList->end(); 
			  ++it )
		{
			m_cboVideoFormat.AddString( CString( it->c_str() ) );
		}


		// Check if there is already a valid video format
		if( !m_pGrabber->getVideoFormat().isValid() )
		{
			m_pGrabber->setVideoFormat( pVidFmtList->at( 0 ) );
		}

		// Select the currently valid video format.
		m_cboVideoFormat.SelectString( -1, CString( m_pGrabber->getVideoFormat().c_str() ) );
	}
	else
	{
        m_cboVideoFormat.AddString( NOT_AVAILABLE );
        m_cboVideoFormat.EnableWindow( false );
        m_cboVideoFormat.SetCurSel( 0 );
	}

	// Update the frame rates since they depend on the video format.
    updateFrameRates();
}


//
// updateInputChannels
//
// Fills the input channel combo box with appropriate values and selects 
// the currently selected input channel.
//
void CDeviceDlg::updateInputChannels()
{
	// Clear combo box
	m_cboInputChannel.ResetContent();

	if( m_pGrabber->isInputChannelAvailableWithCurDev() )
	{
		// Retrieve the list of available input channels.
		Grabber::tInChnListPtr pInChnList = m_pGrabber->getAvailableInputChannels();
		if ( pInChnList == 0 || pInChnList->empty() )
		{
			m_cboInputChannel.AddString( NOT_AVAILABLE );
			m_cboInputChannel.EnableWindow( false );
			m_cboInputChannel.SetCurSel( 0 );
		}

		m_cboInputChannel.EnableWindow( true );

		// Fill the combo box
		for ( Grabber::tInChnList::iterator it = 
			  pInChnList->begin(); 
			  it != pInChnList->end(); 
			  ++it )
		{
			m_cboInputChannel.AddString( CString( it->c_str() ) );
		}

		// Select the currently valid input channel.
		m_cboInputChannel.SelectString( -1, CString( m_pGrabber->getInputChannel().c_str() ) );
	}
	else
	{
		m_cboInputChannel.AddString( NOT_AVAILABLE );
        m_cboInputChannel.EnableWindow( false );
        m_cboInputChannel.SetCurSel( 0 );
	}
}


//
// updateFrameRates
//
// Fills the frame rate combo box with appropriate values and selects 
// the currently selected frame rate.
//
void CDeviceDlg::updateFrameRates()
{
	// Clear combo box
	m_cboFrameRate.ResetContent();
    
	if( m_pGrabber->isFrameRateListAvailable() )
	{
		CString frameRate;

		// Retrieve the list of available frame rates.
		Grabber::tFPSListPtr pFrameRateList = m_pGrabber->getAvailableFPS();
		if ( pFrameRateList == 0 || pFrameRateList->empty() )
		{
			m_cboFrameRate.AddString( NOT_AVAILABLE );
			m_cboFrameRate.EnableWindow( false );
			m_cboFrameRate.SetCurSel( 0 );
		}

		m_cboFrameRate.EnableWindow( true );

		// Fill the combo box
		for ( Grabber::tFPSList::iterator it = 
			  pFrameRateList->begin(); 
			  it != pFrameRateList->end(); 
			  ++it )
		{
			frameRate.Format( TEXT("%lf"), *it );			
			m_cboFrameRate.AddString( frameRate );
		}		

		// Select the currently valid frame rate.
		frameRate.Format( TEXT("%lf"), m_pGrabber->getFPS() );
		m_cboFrameRate.SelectString( -1, frameRate );
	}
	else
	{
		m_cboFrameRate.AddString( NOT_AVAILABLE );
        m_cboFrameRate.EnableWindow( false );
        m_cboFrameRate.SetCurSel( 0 );
	}
}


//
// updateFlip
//
// Updates the check boxes for the horizontal/vertical flip.
//
void CDeviceDlg::updateFlip()
{
	// Check horizontal flip.
	if( m_pGrabber->isFlipHAvailable() )
	{
		m_chkFlipH.EnableWindow( true );
		if( m_pGrabber->getFlipH() )
		{
			m_chkFlipH.SetCheck( 1 );
		}
		else
		{
			m_chkFlipH.SetCheck( 0 );
		}
	}
	else
	{
		m_chkFlipH.EnableWindow( false );
		m_chkFlipH.SetCheck( 0 );
	}
	

	// Check vertical flip.
	if( m_pGrabber->isFlipVAvailable() )
	{
		m_chkFlipV.EnableWindow( true );
		if( m_pGrabber->getFlipV() )
		{
			m_chkFlipV.SetCheck( 1 );
		}
		else
		{
			m_chkFlipV.SetCheck( 0 );
		}
	}
	else
	{
		m_chkFlipV.EnableWindow( false );
		m_chkFlipV.SetCheck( 0 );
	}
}


/////////////////////////////////////////////////////////////////////////////
// Helper Procedures

//
// saveDeviceSettings
//
// saves the state of the currently valid device to the 'Settings' data 
// structure.
//
void CDeviceDlg::saveDeviceSettings()
{
	if( m_pGrabber->isDevValid() )
	{
		m_tDeviceState.bDeviceAvail = true;
		m_tDeviceState.szDevice = m_pGrabber->getDev().c_str();

		if( m_pGrabber->isVideoNormAvailableWithCurDev() )
		{
			m_tDeviceState.bVideoNormAvail = true;
			m_tDeviceState.szVideoNorm = m_pGrabber->getVideoNorm().c_str();
		}
		else
		{
			m_tDeviceState.bVideoNormAvail = false;
		}

		m_tDeviceState.szVideoFormat = m_pGrabber->getVideoFormat().c_str();

		if( m_pGrabber->isFrameRateListAvailable() )
		{
			m_tDeviceState.bFrameRateAvail = true;
			m_tDeviceState.lfFrameRate = m_pGrabber->getFPS();
		}
		else
		{
			m_tDeviceState.bFrameRateAvail = false;
		}

		if( m_pGrabber->isInputChannelAvailableWithCurDev() )
		{
			m_tDeviceState.bInputChannelAvail = true;
			m_tDeviceState.szInputChannel = m_pGrabber->getInputChannel().c_str();
		}
		else
		{
			m_tDeviceState.bInputChannelAvail = false;
		}

		if( m_pGrabber->isFlipVAvailable() )
		{
			m_tDeviceState.bFlipVAvail = true;
			m_tDeviceState.bFlipV = m_pGrabber->getFlipV();
		}
		else
		{
			m_tDeviceState.bFlipVAvail = false;
		}

		if( m_pGrabber->isFlipHAvailable() )
		{
			m_tDeviceState.bFlipHAvail = true;
			m_tDeviceState.bFlipH = m_pGrabber->getFlipH();
		}
		else
		{
			m_tDeviceState.bFlipHAvail = false;
		}
	}
	else
	{
		m_tDeviceState.bDeviceAvail = false;
	}
}

//
// restoreDeviceSettings
//
// restores the state of the a device that was previously
// saved to the 'Settings' data structure.
//
void CDeviceDlg::restoreDeviceSettings()
{
	if( m_tDeviceState.bDeviceAvail )
	{
		m_pGrabber->openDev( m_tDeviceState.szDevice );

		if( m_tDeviceState.bVideoNormAvail )
		{
			m_pGrabber->setVideoNorm( m_tDeviceState.szVideoNorm );
		}

		m_pGrabber->setVideoFormat( m_tDeviceState.szVideoFormat );

		if( m_tDeviceState.bFrameRateAvail )
		{
			m_pGrabber->setFPS( m_tDeviceState.lfFrameRate );
		}

		if( m_tDeviceState.bInputChannelAvail )
		{
			m_pGrabber->setInputChannel( m_tDeviceState.szInputChannel );
		}

		if( m_tDeviceState.bFlipVAvail )
		{
			m_pGrabber->setFlipV( m_tDeviceState.bFlipV );
		}

		if( m_tDeviceState.bFlipHAvail )
		{
			m_pGrabber->setFlipH( m_tDeviceState.bFlipH );
		}
	}
	else
	{
		m_pGrabber->closeDev();
	}
}
