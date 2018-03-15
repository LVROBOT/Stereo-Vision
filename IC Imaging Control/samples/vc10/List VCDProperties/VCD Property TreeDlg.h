// VCD Property TreeDlg.h : header file
//

#if !defined(AFX_VCDPROPERTYTREEDLG_H__6D2F2481_3623_4B4C_8504_91C595E5B1BB__INCLUDED_)
#define AFX_VCDPROPERTYTREEDLG_H__6D2F2481_3623_4B4C_8504_91C595E5B1BB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../Common/VCDPropertyCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CVCDPropertyTreeDlg dialog

using DShowLib::tIVCDPropertyItemsPtr;
using DShowLib::tIVCDPropertyItemPtr;
using DShowLib::tIVCDPropertyElementPtr;
using DShowLib::tIVCDPropertyInterfacePtr;

class CInterfacePath
{
public:
	GUID itemID;
	GUID elementID;
	GUID interfaceID;
};

class CVCDPropertyTreeDlg : public CDialog
{
// Construction
public:
	CVCDPropertyTreeDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CVCDPropertyTreeDlg)
	enum { IDD = IDD_VCDPROPERTYTREE_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVCDPropertyTreeDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

public:
	bool	selectDevice();

// Implementation
protected:
	HICON m_hIcon;

	DShowLib::Grabber	m_Grabber;

	CImageList			m_ImageList;	// Contains graphical elements for the tree view.

	void QueryVCDProperties();
	void QueryVCDPropertyItems( tIVCDPropertyItemsPtr pItems, HTREEITEM hRoot );
	void QueryVCDPropertyElements( tIVCDPropertyItemPtr pItem, HTREEITEM hItem );
	void QueryVCDPropertyInterfaces( tIVCDPropertyElementPtr pElem, HTREEITEM hElem );
	
	void ListAllPropertyItems();

	smart_ptr< CWnd >	m_pCurrentControl;
	smart_ptr< CWnd >	m_pBuddy;
	std::vector< CInterfacePath > m_InterfaceVector;
	// Generated message map functions
	//{{AFX_MSG(CVCDPropertyTreeDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
////////////////////////////////////////
	afx_msg void OnSelectDevice();
	afx_msg void OnShowPage();
	afx_msg void OnSelchangedVcdtree(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VCDPROPERTYTREEDLG_H__6D2F2481_3623_4B4C_8504_91C595E5B1BB__INCLUDED_)
