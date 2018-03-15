// FirstStep.h : main header file for the FIRSTSTEP application
//

#if !defined(AFX_FIRSTSTEP_H__6E82DAE3_B90E_47A4_892B_D39FA479B904__INCLUDED_)
#define AFX_FIRSTSTEP_H__6E82DAE3_B90E_47A4_892B_D39FA479B904__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CFirstStepApp:
// See FirstStep.cpp for the implementation of this class
//

class CFirstStepApp : public CWinApp
{
public:
	CFirstStepApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFirstStepApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CFirstStepApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FIRSTSTEP_H__6E82DAE3_B90E_47A4_892B_D39FA479B904__INCLUDED_)
