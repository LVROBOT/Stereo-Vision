// VCD Property Tree.h : main header file for the VCD PROPERTY TREE application
//

#if !defined(AFX_VCDPROPERTYTREE_H__9678B518_A869_4EAA_A77C_477CE4A2A1A2__INCLUDED_)
#define AFX_VCDPROPERTYTREE_H__9678B518_A869_4EAA_A77C_477CE4A2A1A2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CVCDPropertyTreeApp:
// See VCD Property Tree.cpp for the implementation of this class
//

class CVCDPropertyTreeApp : public CWinApp
{
public:
	CVCDPropertyTreeApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVCDPropertyTreeApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CVCDPropertyTreeApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VCDPROPERTYTREE_H__9678B518_A869_4EAA_A77C_477CE4A2A1A2__INCLUDED_)
