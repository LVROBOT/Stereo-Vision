// VCD Property TreeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "VCD Property Tree.h"
#include "VCD Property TreeDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "../Common/VCDRangeSlider.h"
#include "../Common/VCDSwitchCheck.h"
#include "../Common/VCDButtonButton.h"
#include "../Common/VCDMapStringsCombo.h"
#include "../Common/VCDAbsValSlider.h"

using namespace DShowLib;
/////////////////////////////////////////////////////////////////////////////
// CVCDPropertyTreeDlg dialog

CVCDPropertyTreeDlg::CVCDPropertyTreeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CVCDPropertyTreeDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CVCDPropertyTreeDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	// Create the image list for the tree view and load images
	m_ImageList.Create( 16, 16, ILC_COLOR4, 0, 7 );

	CBitmap bm;
	bm.LoadBitmap( IDB_ITEM );
	m_ImageList.Add( &bm, RGB(0,0,0) );
	bm.Detach();
	bm.LoadBitmap( IDB_VALUE );
	m_ImageList.Add( &bm, RGB(0,0,0) );
	bm.Detach();
	bm.LoadBitmap( IDB_AUTO );
	m_ImageList.Add( &bm, RGB(0,0,0) );
	bm.Detach();
	bm.LoadBitmap( IDB_RANGE );
	m_ImageList.Add( &bm, RGB(0,0,0) );
	bm.Detach();
	bm.LoadBitmap( IDB_SWITCH );
	m_ImageList.Add( &bm, RGB(0,0,0) );
	bm.Detach();
	bm.LoadBitmap( IDB_BUTTON );
	m_ImageList.Add( &bm, RGB(0,0,0) );
	bm.Detach();
	bm.LoadBitmap( IDB_MAPSTRINGS );
	m_ImageList.Add( &bm, RGB(0,0,0) );
	bm.Detach();
}

void CVCDPropertyTreeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CVCDPropertyTreeDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CVCDPropertyTreeDlg, CDialog)
	//{{AFX_MSG_MAP(CVCDPropertyTreeDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SELECT_DEVICE, OnSelectDevice)
	ON_BN_CLICKED(IDC_SHOW_PAGE, OnShowPage)
	ON_NOTIFY(TVN_SELCHANGED, IDC_VCDTREE, OnSelchangedVcdtree)
	ON_WM_HSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVCDPropertyTreeDlg message handlers


BOOL CVCDPropertyTreeDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	// when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

		m_Grabber.setHWND( GetDlgItem( IDC_DISPLAY )->GetSafeHwnd() );
	m_Grabber.startLive();

	CTreeCtrl* pTree = (CTreeCtrl*)GetDlgItem( IDC_VCDTREE );
	pTree->SetImageList( &m_ImageList, TVSIL_NORMAL );

	// Print the property tree to debug out
	ListAllPropertyItems();

	QueryVCDProperties();
		return TRUE;  // return TRUE  unless you set the focus to a control
}

/**
 *	If you add a minimize button to your dialog, you will need the code below
 *	to draw the icon.  For MFC applications using the document/view model,
 *	this is automatically done for you by the framework.
 */
void CVCDPropertyTreeDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CVCDPropertyTreeDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


//////////////////////////////////////////////////////////////////////////
/*! Let the user select a device and make initial settings
*/
bool CVCDPropertyTreeDlg::selectDevice()
{
	m_Grabber.showDevicePage( m_hWnd );

	return m_Grabber.isDevValid();
}

/**
 * Show the built-in Device selection page
 */
void CVCDPropertyTreeDlg::OnSelectDevice() 
{
	// Live mode has to be stopped before showing the device page
	m_Grabber.stopLive();

	// Show device page
	m_Grabber.showDevicePage( m_hWnd );

	// start live mode if a valid device is selected
	if( m_Grabber.isDevValid() )
		m_Grabber.startLive();

	// Print the property tree to debug out
	ListAllPropertyItems();

	// Re-Build the tree
	QueryVCDProperties();
}

/**
 * Show the built-in VCD Property Page
 */
void CVCDPropertyTreeDlg::OnShowPage() 
{
	// Show the property page
	m_Grabber.showVCDPropertyPage( m_hWnd );	
}

/**
 * QueryVCDProperties clears the tree control and calls QueryVCDPropertyItems
 * to retrieve all VCDPropertyItems and insert them into the tree control.
 */
void CVCDPropertyTreeDlg::QueryVCDProperties()
{
	CTreeCtrl* pTree = (CTreeCtrl*)GetDlgItem( IDC_VCDTREE );

	// Clear the tree
	pTree->DeleteAllItems();

	// Insert the root item
	HTREEITEM hRoot = pTree->InsertItem( TEXT("VCD Properties") );

	// Set item data to MAXDWORD, because this is not an interface.
	pTree->SetItemData( hRoot, MAXDWORD );

	tIVCDPropertyItemsPtr pVCDProperties = m_Grabber.getAvailableVCDProperties();
	if( pVCDProperties != 0 )
	{	
		QueryVCDPropertyItems( pVCDProperties, hRoot );
	}

	// Make sure the tree is expanded
	pTree->Expand( hRoot, TVE_EXPAND );
}

/**
 * Retrieve all available VCDPropertyItems that are contained in the
 * VCDPropertyItems collection. For each VCDPropertyItem call the sub
 * QueryVCDPropertyElements to retrieve all VCDPropertyElements of the current property
 * item.
 */
void CVCDPropertyTreeDlg::QueryVCDPropertyItems( tIVCDPropertyItemsPtr pItems, HTREEITEM hRoot )
{
	CTreeCtrl* pTree = (CTreeCtrl*)GetDlgItem( IDC_VCDTREE );

	// Iterate through the items, insert them into the tree and query for their elements.
	tVCDPropertyItemArray itemArray = pItems->getItems();
	for( tVCDPropertyItemArray::const_iterator i = itemArray.begin(); i != itemArray.end(); ++i )
	{
		// Insert an item node.
		HTREEITEM hItem = pTree->InsertItem( CString( (*i)->getName().c_str() ), 0, 0, hRoot );

		// Set node data to MAXDWORD.
		pTree->SetItemData( hItem, MAXDWORD );

		// Query for elements
		QueryVCDPropertyElements( *i, hItem );

		// Make sure the tree is expanded.
		pTree->Expand( hItem, TVE_EXPAND );
	}
}

/**
 * Query all VCDPropertyElements of the passed VCDPropertyItem and insert them
 * into the tree control. Then retrieve all interfaces of the VCDPropertyElements
 * by a call to QueryVCDPropertyInterface.
 */
void CVCDPropertyTreeDlg::QueryVCDPropertyElements( tIVCDPropertyItemPtr pItem, HTREEITEM hItem )
{
	CTreeCtrl* pTree = (CTreeCtrl*)GetDlgItem( IDC_VCDTREE );

	CString name;
	int imgIndex;

	tVCDPropertyElementArray elemArray = pItem->getElements();
	for( tVCDPropertyElementArray::const_iterator i = elemArray.begin(); i != elemArray.end(); ++i )
	{

		GUID eid = (*i)->getElementID();
		if( eid == VCDElement_Value )
		{
			name = "VCDElement_Value";
			imgIndex = 1;
		}
		else if( eid == VCDElement_Auto )
		{
			name = "VCDElement_Auto";
			imgIndex = 2;
		}
		else if( eid == VCDElement_OnePush )
		{
			name = "VCDElement_OnePush";
			imgIndex = 5;
		}
		else if( eid == VCDElement_WhiteBalanceBlue )
		{
			name = "VCDElement_WhiteBalanceBlue";
			imgIndex = 1;
		}
		else if( eid == VCDElement_WhiteBalanceRed )
		{
			name = "VCDElement_WhiteBalanceRed";
			imgIndex = 1;
		}
		else
		{
			name = "Unknown element";
			imgIndex = 1;
		}

		name = name + ": '" + (*i)->getName().c_str() + "'";

		HTREEITEM hElem = pTree->InsertItem( name, imgIndex, imgIndex, hItem );

		// Set node data to MAXDWORD.
		pTree->SetItemData( hElem, MAXDWORD );

		QueryVCDPropertyInterfaces( *i, hElem );

		pTree->Expand( hElem, TVE_EXPAND );
	}
}

/**
 * QueryVCDPropertyInterfaces
 *
 * Query all interfaces of the passed VCDPropertyElement.
 * For each found interface, an entry is added to the tree control and the interface
 * pointer is stored in a map entry associated with the tree node.
 */
void CVCDPropertyTreeDlg::QueryVCDPropertyInterfaces( tIVCDPropertyElementPtr pElem, HTREEITEM hElem )
{
	CTreeCtrl* pTree = (CTreeCtrl*)GetDlgItem( IDC_VCDTREE );

	CWnd* pCtrl = 0;

	CString name;
	int imgIndex;

	tVCDPropertyInterfaceArray itfArray = pElem->getInterfaces();
	for( tVCDPropertyInterfaceArray::const_iterator i = itfArray.begin(); i != itfArray.end(); ++i )
	{
		GUID iid = (*i)->getInterfaceID();
		if( iid == IID_IVCDRangeProperty )
		{
			name = "Range";
			imgIndex = 3;
		}
		else if( iid == IID_IVCDSwitchProperty )
		{
			name = "Switch";
			imgIndex = 4;
		}
		else if( iid == IID_IVCDButtonProperty )
		{
			name = "Button";
			imgIndex = 5;
		}
		else if( iid == IID_IVCDMapStringsProperty )
		{
			name = "MapStrings";
			imgIndex = 6;
		}
		else if( iid == IID_IVCDAbsoluteValueProperty )
		{
			name = "AbsoluteValue";
			imgIndex = 3;
		}
		else 
		{
			name = "Unknown Interface";
			imgIndex = 3;
		}

		// Insert the interface item
		HTREEITEM hItf = pTree->InsertItem( name, imgIndex, imgIndex, hElem );

		// Store the interface path within the vector.
		CInterfacePath ItfPath;

		ItfPath.itemID = (*i)->getParent()->getParent()->getItemID();
		ItfPath.elementID = (*i)->getParent()->getElementID();
		ItfPath.interfaceID = (*i)->getInterfaceID();

		m_InterfaceVector.push_back( ItfPath );

		// Store the position in the vector as node data
		pTree->SetItemData( hItf, m_InterfaceVector.size()-1 );
	}
}

/**
 *	This event is raised when the user selects a tree node.
 *
 *	The item data of the clicked node is evaluated and used as an index into the
 *	vector if interfaces that was built when filling the tree view.
 *	After that, the interface found is asked for its type and an appropriate control
 *	is created to let the user control the interface.
 */
void CVCDPropertyTreeDlg::OnSelchangedVcdtree(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	CTreeCtrl* pTree = (CTreeCtrl*)GetDlgItem( IDC_VCDTREE );

	DWORD index = pTree->GetItemData( pNMTreeView->itemNew.hItem );

	// If the index equals MAXDWORD, the node is not a leaf.
	if( index == MAXDWORD )
		return;

	// Destroy the buddy window
	m_pBuddy = 0;

	// Retrieve the interface path
	CInterfacePath ItfPath = m_InterfaceVector.at( index );
		
	// Get a pointer to the interface specified by itemID, elementID and interfaceID.
	tIVCDPropertyInterfacePtr pItf = m_Grabber.getAvailableVCDProperties()->findInterface( ItfPath.itemID, 
																						   ItfPath.elementID,
																						   ItfPath.interfaceID );

	// Build an appropriate text for the frame.
	CString frameText( pItf->getParent()->getParent()->getName().c_str() );

	// Test whether the interface is IVCDRangeProperty 
	if( ItfPath.interfaceID == IID_IVCDRangeProperty )
	{
		// Acquire the interface pointer
		tIVCDRangePropertyPtr pRangeItf;
		pItf->QueryInterface( pRangeItf );
		if( pRangeItf == 0 )
			return;

		// Create a range slider control
		CVCDRangeSlider* pSlider = new CVCDRangeSlider();
		pSlider->Create( WS_CHILD|TBS_NOTICKS, CRect( 300, 450, 500, 480 ), this, 0 );		

		// Create a buddy window to display the value text
		CStatic* pBuddy = new CStatic();
		pBuddy->Create( TEXT("0"), WS_VISIBLE|WS_CHILD|SS_CENTERIMAGE, CRect( 0, 0, 100, 23 ), this );
		pBuddy->SetFont( GetDlgItem( IDC_VCDTREE )->GetFont() );
		pSlider->SetBuddy( pBuddy, FALSE );
		m_pBuddy = pBuddy;

		pSlider->setupCtrl( pRangeItf );

		m_pCurrentControl = pSlider;

		// Add the element name to the frame text
		frameText += TEXT(": ");
		frameText += pItf->getParent()->getName().c_str();
	}
	// Test whether the interface is IVCDSwitchProperty 
	else if( ItfPath.interfaceID == IID_IVCDSwitchProperty )
	{
		// Acquire the interface pointer
		tIVCDSwitchPropertyPtr pSwitchItf;
		pItf->QueryInterface( pSwitchItf );
		if( pSwitchItf == 0 )
			return;

		// Create a switch check control
		CVCDSwitchCheck* pButton = new CVCDSwitchCheck();
		pButton->Create( CString( pItf->getParent()->getName().c_str() ), WS_CHILD|BS_CHECKBOX, CRect( 300, 450, 500, 480 ), this, 0 );
		pButton->SetFont( GetDlgItem( IDC_VCDTREE )->GetFont() );
		pButton->setupCtrl( pSwitchItf, 0 );

		m_pCurrentControl = pButton;
	}
	// Test whether the interface is IVCDButtonProperty 
	else if( ItfPath.interfaceID == IID_IVCDButtonProperty )
	{
		// Acquire the interface pointer
		tIVCDButtonPropertyPtr pButtonItf;
		pItf->QueryInterface( pButtonItf );
		if( pButtonItf == 0 )
			return;

		// Create a button control
		CVCDButtonButton* pButton = new CVCDButtonButton();
		pButton->Create( CString( pItf->getParent()->getName().c_str() ), WS_CHILD|BS_PUSHBUTTON, CRect( 300, 450, 380, 474 ), this, 0 );
		pButton->SetFont( GetDlgItem( IDC_VCDTREE )->GetFont() );
		pButton->setupCtrl( pButtonItf, 0 );

		m_pCurrentControl = pButton;
	}
	// Test whether the interface is IVCDMapStringsProperty 
	else if( ItfPath.interfaceID == IID_IVCDMapStringsProperty )
	{
		// Acquire the interface pointer
		tIVCDMapStringsPropertyPtr pMapStringsItf;
		pItf->QueryInterface( pMapStringsItf );
		if( pMapStringsItf == 0 )
			return;

		// Create a combo control
		CVCDMapStringsCombo* pCombo = new CVCDMapStringsCombo();
		pCombo->Create( WS_CHILD|CBS_DROPDOWNLIST|WS_VSCROLL, CRect( 300, 450, 500, 550 ), this, 0 );
		pCombo->SetFont( GetDlgItem( IDC_VCDTREE )->GetFont() );
		pCombo->setupCtrl( pMapStringsItf );

		m_pCurrentControl = pCombo;

		// Add the element name to the frame text
		frameText += TEXT(": ");
		frameText += pItf->getParent()->getName().c_str();
	}
	// Test whether the interface is IVCDAbsoluteValueProperty 
	else if( ItfPath.interfaceID == IID_IVCDAbsoluteValueProperty )
	{
		// Acquire the interface pointer
		tIVCDAbsoluteValuePropertyPtr pAbsValItf;
		pItf->QueryInterface( pAbsValItf );
		if( pAbsValItf == 0 )
			return;

		// Create a absolute value slider control
		CVCDAbsValSlider* pSlider = new CVCDAbsValSlider();
		pSlider->Create( WS_CHILD|TBS_NOTICKS, CRect( 300, 450, 500, 480 ), this, 0 );		

		CStatic* pBuddy = new CStatic();
		pBuddy->Create( TEXT("0"), WS_VISIBLE|WS_CHILD|SS_CENTERIMAGE, CRect( 0, 0, 100, 23 ), this );
		pBuddy->SetFont( GetDlgItem( IDC_VCDTREE )->GetFont() );
		pSlider->SetBuddy( pBuddy, FALSE );
		m_pBuddy = pBuddy;

		pSlider->setupCtrl( pAbsValItf );

		m_pCurrentControl = pSlider;

		// Add the element name to the frame text
		frameText += TEXT(": ");
		frameText += pItf->getParent()->getName().c_str();
	}

	// Show the control in case it was (initially) hidden
	if( m_pCurrentControl != 0 )
		m_pCurrentControl->ShowWindow( SW_SHOW );

	// Set the frame title
	GetDlgItem( IDC_CTRL_FRAME )->SetWindowText( frameText );

	*pResult = 0;
}

void CVCDPropertyTreeDlg::ListAllPropertyItems()
{
	OutputDebugString( TEXT("\n\nVCD Tree:\n\n") );

	// Get all property items
	tIVCDPropertyItemsPtr pVCDProperties = m_Grabber.getAvailableVCDProperties();
	if( pVCDProperties != 0 )
	{	
		// Iterate through the items and print the names.
		tVCDPropertyItemArray itemArray = pVCDProperties->getItems();
		for( tVCDPropertyItemArray::const_iterator itItem = itemArray.begin(); itItem != itemArray.end(); ++itItem )
		{
			// Print the item name 
			OutputDebugString( CString( (*itItem)->getName().c_str() ) );
			OutputDebugString( TEXT("\n") );

			// Iterate through the elements and print the names.
			tVCDPropertyElementArray elemArray = (*itItem)->getElements();
			for( tVCDPropertyElementArray::iterator itElem = elemArray.begin(); itElem != elemArray.end(); ++itElem )
			{
				// Print the element name 
				OutputDebugString( TEXT("   Element : ") );
				OutputDebugString( CString( (*itElem)->getName().c_str() ) );
				OutputDebugString( TEXT("\n") );

				// Iterate through the interfaces and print the names.
				tVCDPropertyInterfaceArray itfArray = (*itElem)->getInterfaces();
				for( tVCDPropertyInterfaceArray::const_iterator itItf = itfArray.begin(); itItf != itfArray.end(); ++itItf )
				{
					// Check the interface type and print the name 
					OutputDebugString( TEXT("		Interface : ") );

					GUID iid = (*itItf)->getInterfaceID();

					if( iid == IID_IVCDAbsoluteValueProperty )
					{
						OutputDebugString( TEXT("Absolute Value\n") );
					}
					else if( iid == IID_IVCDMapStringsProperty )
					{
						OutputDebugString( TEXT("Mapstrings\n") );
					}
					else if( iid ==  IID_IVCDSwitchProperty )
					{
						OutputDebugString( TEXT("Switch\n") );
					}
					else if( iid == IID_IVCDButtonProperty )
					{
						OutputDebugString( TEXT("Button\n") );
					}
					else if( iid == IID_IVCDRangeProperty )
					{
						OutputDebugString( TEXT("Range\n") );
					}
				}
			}
		}
	}
}

/**
 *	This event is raised when one of the inserted trackbars is scrolled
 *
 *	Scroll messages are always sent to the parent window, so we forward the message
 *	to the control so it can handle it.
 */
void CVCDPropertyTreeDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// Propagate scroll messages to the trackbars.
	pScrollBar->SendMessage( WM_HSCROLL, MAKEWPARAM( nSBCode, nPos ), (LPARAM)pScrollBar->m_hWnd );
	
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

