// FirstStepDoc.cpp : implementation of the CFirstStepDoc class
//

#include "stdafx.h"
#include "FirstStep.h"

#include "FirstStepDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFirstStepDoc

IMPLEMENT_DYNCREATE(CFirstStepDoc, CDocument)

BEGIN_MESSAGE_MAP(CFirstStepDoc, CDocument)
	//{{AFX_MSG_MAP(CFirstStepDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFirstStepDoc construction/destruction

CFirstStepDoc::CFirstStepDoc()
{
	// TODO: add one-time construction code here
	m_pGrabber = new DShowLib::Grabber();
	ASSERT( m_pGrabber );
}

CFirstStepDoc::~CFirstStepDoc()
{
	delete m_pGrabber;
}

BOOL CFirstStepDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CFirstStepDoc serialization

void CFirstStepDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CFirstStepDoc diagnostics

#ifdef _DEBUG
void CFirstStepDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CFirstStepDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFirstStepDoc commands

void CFirstStepDoc::OnCloseDocument() 
{
	// TODO: Add your specialized code here and/or call the base class

	// Stop live mode.
	m_pGrabber->stopLive();
   
	// this call will also succeed if no device is open
	m_pGrabber->closeDev();
	
	CDocument::OnCloseDocument();
}
//>>