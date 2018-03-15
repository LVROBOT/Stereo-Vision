// DigitalIODlg.h : header file
//

#if !defined(AFX_VCDSIMPLEPROPERTYDLG_H__FE179C98_4D80_4DFD_BE48_89A5E3BE32BF__INCLUDED_)
#define AFX_VCDSIMPLEPROPERTYDLG_H__FE179C98_4D80_4DFD_BE48_89A5E3BE32BF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../Common/SimplePropertyAccess.h"
/////////////////////////////////////////////////////////////////////////////
// DigitalIODlg dialog

class DigitalIODlg : public CDialog
{
// Construction
public:
	bool selectDevice();
	DigitalIODlg(CWnd* pParent = NULL);	// standard constructor



// Dialog Data
	//{{AFX_DATA(DigitalIODlg)
	enum { IDD = IDD_VCDSIMPLEPROPERTY_DIALOG };
	CButton	m_chkDigitalOutputState;
	CButton	m_chkDigitalInputState;
	CButton	m_cButtonWriteOutput;
	CButton	m_cButtonReadInput;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DigitalIODlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	DShowLib::Grabber m_Grabber;

	// An instance of the helper class
	CSimplePropertyAccess m_VCDProp;


	// Generated message map functions
	//{{AFX_MSG(DigitalIODlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonreadinput();
	afx_msg void OnButtonwriteoutput();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void InitControls();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VCDSIMPLEPROPERTYDLG_H__FE179C98_4D80_4DFD_BE48_89A5E3BE32BF__INCLUDED_)
