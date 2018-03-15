// BinarizationDlg.h : header file
//

#pragma once

#include "BinarizationFilter.h"

// CBinarizationDlg dialog
class CBinarizationDlg : public CDialog
{
// Construction
public:
	CBinarizationDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_BINARIZATION_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	DShowLib::Grabber					m_Grabber;
	CBinarizationFilter					m_binarizationFilter;

	void alignRight( UINT ctrlID, int width, int dist );
	void alignBottom( UINT ctrlID, int height, int dist );

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedDevice();
	afx_msg void OnBnClickedProperties();
	afx_msg void OnBnClickedClose();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	afx_msg void OnBnClickedBinarizeEnable();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnClose();
private:
	CButton m_BinarizeEnable;
	CSliderCtrl m_BinarizeThreshold;
	CStatic m_BinarizeThresholdStatic;
};
