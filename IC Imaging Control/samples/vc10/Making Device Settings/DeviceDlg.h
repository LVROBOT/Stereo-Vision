#if !defined(AFX_DEVICEDLG_H__E0D060C1_199B_420D_BDDE_FF7DBC77A03A__INCLUDED_)
#define AFX_DEVICEDLG_H__E0D060C1_199B_420D_BDDE_FF7DBC77A03A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DeviceDlg.h : header file
//

#include "tisudshl.h"

using namespace DShowLib;

#define NOT_AVAILABLE	TEXT("n\\a")

struct Settings
{
    bool bDeviceAvail;
	std::string szDevice;
    
    bool bVideoNormAvail;
    std::string szVideoNorm;
    
    std::string szVideoFormat;
    
    bool bFrameRateAvail;
    double lfFrameRate;
    
    bool bInputChannelAvail;
    std::string szInputChannel;
    
    bool bFlipVAvail;
    bool bFlipV;
        
    bool bFlipHAvail;
    bool bFlipH;
};

/////////////////////////////////////////////////////////////////////////////
// CDeviceDlg dialog

class CDeviceDlg : public CDialog
{
// Construction
public:
	CDeviceDlg( Grabber* pGrabber, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDeviceDlg)
	enum { IDD = IDD_DEVICE_SETTINGS };
	CButton	m_chkFlipH;
	CButton	m_chkFlipV;
	CStatic	m_staticSerialOut;
	CComboBox	m_cboVideoNorm;
	CComboBox	m_cboVideoFormat;
	CComboBox	m_cboInputChannel;
	CComboBox	m_cboFrameRate;
	CComboBox	m_cboDevice;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDeviceDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDeviceDlg)
	virtual void OnCancel();
	afx_msg void OnSelchangeComboDevice();
	afx_msg void OnSelchangeComboFramerate();
	afx_msg void OnSelchangeComboInputchannel();
	afx_msg void OnSelchangeComboVideoformat();
	afx_msg void OnSelchangeComboVideonorm();
	afx_msg void OnCheckFliph();
	afx_msg void OnCheckFlipv();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()


private:

	void saveDeviceSettings();
	void restoreDeviceSettings();

    void updateDevices();
	void updateVideoNorms();
	void updateVideoFormats();
	void updateInputChannels();
	void updateFrameRates();
	void updateFlip();
	
		Grabber*	m_pGrabber;
	Settings	m_tDeviceState;
	};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DEVICEDLG_H__E0D060C1_199B_420D_BDDE_FF7DBC77A03A__INCLUDED_)
