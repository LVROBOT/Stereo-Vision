// VCD SimpleDlg.h : header file
//

#if !defined(AFX_VCDSIMPLEDLG_H__CD91E489_2C53_4A36_8DAE_847A9DBC9522__INCLUDED_)
#define AFX_VCDSIMPLEDLG_H__CD91E489_2C53_4A36_8DAE_847A9DBC9522__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CVCDSimpleDlg dialog

class CVCDSimpleDlg : public CDialog
{
// Construction
public:
	CVCDSimpleDlg(CWnd* pParent = NULL);	// standard constructor

	bool selectDevice();

// Dialog Data
	//{{AFX_DATA(CVCDSimpleDlg)
	enum { IDD = IDD_VCDSIMPLE_DIALOG };
	CButton	m_BrightnessAutoCheck;
	CSliderCtrl	m_BrightnessSlider;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVCDSimpleDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	DShowLib::Grabber					m_Grabber;

		DShowLib::tIVCDRangePropertyPtr		m_pBrightnessRange;
	DShowLib::tIVCDSwitchPropertyPtr	m_pBrightnessAuto;
	
	void InitPropertyControls();
	void UpdateControls();

	// Generated message map functions
	//{{AFX_MSG(CVCDSimpleDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSelectDevice();
	afx_msg void OnBrightnessCheck();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VCDSIMPLEDLG_H__CD91E489_2C53_4A36_8DAE_847A9DBC9522__INCLUDED_)
