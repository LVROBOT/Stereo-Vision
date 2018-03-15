// FirstStepView.cpp : implementation of the CFirstStepView class
//

#include "stdafx.h"
#include "FirstStep.h"

#include "FirstStepDoc.h"
#include "FirstStepView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFirstStepView

IMPLEMENT_DYNCREATE(CFirstStepView, CView)

BEGIN_MESSAGE_MAP(CFirstStepView, CView)
	//{{AFX_MSG_MAP(CFirstStepView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFirstStepView construction/destruction

CFirstStepView::CFirstStepView()
{
	// TODO: add construction code here

}

CFirstStepView::~CFirstStepView()
{
}

BOOL CFirstStepView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CFirstStepView drawing

void CFirstStepView::OnDraw(CDC* pDC)
{
	CFirstStepDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CFirstStepView diagnostics

#ifdef _DEBUG
void CFirstStepView::AssertValid() const
{
	CView::AssertValid();
}

void CFirstStepView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CFirstStepDoc* CFirstStepView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFirstStepDoc)));
	return (CFirstStepDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFirstStepView message handlers

void CFirstStepView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class

	// Get the grabber from the document class.
	DShowLib::Grabber* pGrabber = GetDocument()->m_pGrabber;
	
	// Show the device page.
	pGrabber->showDevicePage();

	// Check if there is a valid device.
	if( pGrabber->isDevValid() )
	{
		// Set the window that should display the live video.
        pGrabber->setHWND( m_hWnd );	
		// Start the live video.
        pGrabber->startLive();	
	}
	else
	{
		AfxMessageBox( TEXT("No device was selected.") );
	}
}
//>>