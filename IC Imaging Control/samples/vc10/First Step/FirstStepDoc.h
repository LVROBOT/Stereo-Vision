// FirstStepDoc.h : interface of the CFirstStepDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_FIRSTSTEPDOC_H__11AC77CC_0BEE_4228_8A3E_42A0B05490CF__INCLUDED_)
#define AFX_FIRSTSTEPDOC_H__11AC77CC_0BEE_4228_8A3E_42A0B05490CF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CFirstStepDoc : public CDocument
{
protected: // create from serialization only
	CFirstStepDoc();
	DECLARE_DYNCREATE(CFirstStepDoc)

// Attributes
public:
		DShowLib::Grabber* m_pGrabber;
	
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFirstStepDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual void OnCloseDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CFirstStepDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CFirstStepDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FIRSTSTEPDOC_H__11AC77CC_0BEE_4228_8A3E_42A0B05490CF__INCLUDED_)
