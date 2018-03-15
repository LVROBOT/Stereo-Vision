// ScrollAndZoom.h : main header file for the ScrollAndZoom application
//

#if !defined(AFX_ScrollAndZoom_H__FBCD3DF1_5674_47DF_AAB4_8900C12CFD42__INCLUDED_)
#define AFX_ScrollAndZoom_H__FBCD3DF1_5674_47DF_AAB4_8900C12CFD42__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CScrollAndZoomApp:
// See ScrollAndZoom.cpp for the implementation of this class
//

class CScrollAndZoomApp : public CWinApp
{
public:
	CScrollAndZoomApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScrollAndZoomApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

public:
	//{{AFX_MSG(CScrollAndZoomApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


#define REG_SECTION_DEVICE	TEXT("DeviceSettings")
#define REG_DEVICE			TEXT("VideoDevice")
#define REG_DEVICE_VSOURCE	TEXT("VideoSource")
#define REG_DEVICE_VNORM	TEXT("VideoNorm")
#define REG_DEVICE_VFORMAT	TEXT("VideoFormat")
#define REG_DEVICE_ICHANNEL	TEXT("InputChannel")
#define REG_DEVICE_SETSIZE	TEXT("SetWindowSize")
#define REG_SECTION_AVI		TEXT("AviFileSettings")
#define REG_FILENAME		TEXT("AviFilename")
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ScrollAndZoom_H__FBCD3DF1_5674_47DF_AAB4_8900C12CFD42__INCLUDED_)
