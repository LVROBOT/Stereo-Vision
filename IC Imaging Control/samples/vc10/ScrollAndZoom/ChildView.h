// ChildView.h : interface of the CChildView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHILDVIEW_H__9E3647E0_2CDC_4912_BC21_5F0EAC73BFED__INCLUDED_)
#define AFX_CHILDVIEW_H__9E3647E0_2CDC_4912_BC21_5F0EAC73BFED__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CChildView window

class CChildView : public CWnd
{
// Construction
public:
	CChildView(DShowLib::Grabber* pGrabber);

// Attributes
public:

// Operations
public:

	void showBuffer( const DShowLib::Grabber::tMemBufferPtr& pBuffer );

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChildView)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	void PaintImage();
	virtual ~CChildView();
	void SetupScrollBars();

	// Generated message map functions
protected:
	//{{AFX_MSG(CChildView)
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	DShowLib::Grabber* m_pGrabber;
	DShowLib::Grabber::tMemBufferPtr m_pBuffer;	
	bool m_bdonoterase;

	void EraseBackground(CDC* pDC);
	void OnScroll(UINT nSBCode, UINT nPos, int iScrollBar);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHILDVIEW_H__9E3647E0_2CDC_4912_BC21_5F0EAC73BFED__INCLUDED_)
