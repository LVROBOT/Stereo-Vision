// MakingDeviceSettings.h : main header file for the MAKINGDEVICESETTINGS application
//

#if !defined(AFX_MAKINGDEVICESETTINGS_H__1A134050_575B_4C47_B60D_DBCB97CCC964__INCLUDED_)
#define AFX_MAKINGDEVICESETTINGS_H__1A134050_575B_4C47_B60D_DBCB97CCC964__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMakingDeviceSettingsApp:
// See MakingDeviceSettings.cpp for the implementation of this class
//

class CMakingDeviceSettingsApp : public CWinApp
{
public:
	CMakingDeviceSettingsApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMakingDeviceSettingsApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMakingDeviceSettingsApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()	
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAKINGDEVICESETTINGS_H__1A134050_575B_4C47_B60D_DBCB97CCC964__INCLUDED_)
