// VCD Simple.h : main header file for the VCD SIMPLE application
//

#if !defined(AFX_VCDSIMPLE_H__B1DB3C31_C83C_4E2E_B03E_EB70919FFD35__INCLUDED_)
#define AFX_VCDSIMPLE_H__B1DB3C31_C83C_4E2E_B03E_EB70919FFD35__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CVCDSimpleApp:
// See VCD Simple.cpp for the implementation of this class
//

class CVCDSimpleApp : public CWinApp
{
public:
	CVCDSimpleApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVCDSimpleApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CVCDSimpleApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VCDSIMPLE_H__B1DB3C31_C83C_4E2E_B03E_EB70919FFD35__INCLUDED_)
