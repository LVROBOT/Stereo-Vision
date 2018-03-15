// FirstStepView.h : interface of the CFirstStepView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_FIRSTSTEPVIEW_H__DB3C18D3_4B17_4C51_8BC2_3E39EAAC120A__INCLUDED_)
#define AFX_FIRSTSTEPVIEW_H__DB3C18D3_4B17_4C51_8BC2_3E39EAAC120A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CFirstStepView : public CView
{
protected: // create from serialization only
	CFirstStepView();
	DECLARE_DYNCREATE(CFirstStepView)

// Attributes
public:
	CFirstStepDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFirstStepView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CFirstStepView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CFirstStepView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in FirstStepView.cpp
inline CFirstStepDoc* CFirstStepView::GetDocument()
   { return (CFirstStepDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FIRSTSTEPVIEW_H__DB3C18D3_4B17_4C51_8BC2_3E39EAAC120A__INCLUDED_)
