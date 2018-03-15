// MakingDeviceSettingsDlg.h : header file
//

#if !defined(AFX_MAKINGDEVICESETTINGSDLG_H__006DCFA6_DA33_418A_803A_0009EED89DB6__INCLUDED_)
#define AFX_MAKINGDEVICESETTINGSDLG_H__006DCFA6_DA33_418A_803A_0009EED89DB6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

using namespace DShowLib;

/////////////////////////////////////////////////////////////////////////////
// CMakingDeviceSettingsDlg dialog

class CMakingDeviceSettingsDlg : public CDialog
{
// Construction
public:
	CMakingDeviceSettingsDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMakingDeviceSettingsDlg)
	enum { IDD = IDD_MAKINGDEVICESETTINGS_DIALOG };
	CStatic	m_staticPicture;
	CButton	m_btnStopLive;
	CButton	m_btnStartLive;
	CButton	m_btnDevice;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMakingDeviceSettingsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMakingDeviceSettingsDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnStartlive();
	afx_msg void OnBtnStoplive();
	afx_msg void OnBtnDevice();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	DShowLib::Grabber	m_Grabber;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAKINGDEVICESETTINGSDLG_H__006DCFA6_DA33_418A_803A_0009EED89DB6__INCLUDED_)
