// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__014CF740_70E2_4EEF_9355_917E1DE14EE0__INCLUDED_)
#define AFX_MAINFRM_H__014CF740_70E2_4EEF_9355_917E1DE14EE0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ChildView.h"

#include "tisudshl.h"
#include "overlaycallback.h"
#include "../Dialogs/Dialogs.h"

class CMainFrame
	:	public CFrameWnd,
		public DShowLib::GrabberListener
{
	
public:
	CMainFrame();
	~CMainFrame();
protected: 
	DECLARE_DYNAMIC(CMainFrame)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	void	LoadPreviouslyUsedDevice();
	void	resizeToVideoFormat();
	void	updateWindowTitle();

	virtual void	frameReady( DShowLib::Grabber& caller, smart_ptr<DShowLib::MemBuffer> pBuffer, DWORD FrameNumber );

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CToolBar    m_wndToolBar;
	CChildView    m_wndView;
	HWND		m_hWndSinkDisplay;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	afx_msg void OnSettingsDevice();
	afx_msg void OnSettingsImage();
	afx_msg void OnPreviewStart();
	afx_msg void OnPreviewStop();
	afx_msg void OnFileSaveimage();
	afx_msg void OnFileWriteavi();
	afx_msg void OnUpdatePreviewStart(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePreviewStop(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSettingsImage(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFileSaveimage(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFileWriteavi(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSettingsDevice(CCmdUI* pCmdUI);
	afx_msg void OnClose();
	afx_msg void OnAppExit();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnButtontriggertoggle();
	afx_msg void OnUpdateButtontriggertoggle(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	DShowLib::Grabber							m_Grabber;
	DShowLib::FrameHandlerSink::tFHSPtr			m_pSink;

	smart_ptr<tMediaStreamSinkDialogSettings>	m_pMediaStreamSinkDialogSettings;

	BOOL m_IsStillImageValid;
	void displayTime();							///< Display the current time in the video image
	COverlayCallback m_cOverlayCallback;		///< Class for the callback function

	void toggleOverlayAtPosition( DShowLib::tPathPosition pos );
	void setOverlayBitmapColorMode( DShowLib::OverlayBitmap::tOVBColorMode mode );

public:
	afx_msg void OnOverlayDisplay();
	afx_msg void OnUpdateOverlayDisplay(CCmdUI *pCmdUI);
	afx_msg void OnOverlaySink();
	afx_msg void OnUpdateOverlaySink(CCmdUI *pCmdUI);
	afx_msg void OnOverlayDevice();
	afx_msg void OnUpdateOverlayDevice(CCmdUI *pCmdUI);

public:
	void updateOverlayChecks();
	void drawOverlay( DShowLib::tPathPosition pos );
	afx_msg void OnOverlaycolormodeBESTFIT();
	afx_msg void OnUpdateOverlaycolormodeBESTFIT(CCmdUI *pCmdUI);
	afx_msg void OnOverlaycolormodeGRAYSCALE();
	afx_msg void OnUpdateOverlaycolormodeGRAYSCALE(CCmdUI *pCmdUI);
	afx_msg void OnOverlaycolormodeCOLOR();
	afx_msg void OnUpdateOverlaycolormodeCOLOR(CCmdUI *pCmdUI);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__014CF740_70E2_4EEF_9355_917E1DE14EE0__INCLUDED_)
