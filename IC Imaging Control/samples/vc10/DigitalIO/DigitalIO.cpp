// DigitalIO.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "DigitalIO.h"
#include "DigitalIODlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DigitalIOApp

BEGIN_MESSAGE_MAP(DigitalIOApp, CWinApp)
	//{{AFX_MSG_MAP(DigitalIOApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DigitalIOApp construction

DigitalIOApp::DigitalIOApp()
{
	// Clear memory leaks at end of the program.
	atexit( _DSHOWLIB_NAMESPACE::ExitLibrary );

	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only DigitalIOApp object

DigitalIOApp theApp;

/////////////////////////////////////////////////////////////////////////////
// DigitalIOApp initialization

BOOL DigitalIOApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.


#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	DigitalIODlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal(); 
	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
