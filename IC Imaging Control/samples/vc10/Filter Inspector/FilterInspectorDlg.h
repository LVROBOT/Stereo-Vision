// FilterListerDlg.h : header file
//

#pragma once


// CFilterInspectorDlg dialog
class CFilterInspectorDlg : public CDialog
{
// Construction
public:
	CFilterInspectorDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_FILTERINSPECTOR_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Grabber instance for this dialog
	DShowLib::Grabber						m_Grabber;

	// List with filter path names
	typedef std::vector<std::string>		tFilterFileInfoList;
	tFilterFileInfoList						m_FilterFileList;

	// Current filter
	smart_com<DShowLib::IFrameFilter>		m_pFilter;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedDevice();
	afx_msg void OnBnClickedProperties();
	afx_msg void OnLbnSelchangeFiles();
	afx_msg void OnLbnSelchangeFilters();
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnClose();
	afx_msg void OnBnClickedDialog();
	afx_msg void Startlive();
	afx_msg void Stoplive();
};
