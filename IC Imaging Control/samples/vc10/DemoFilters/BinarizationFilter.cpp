#include "StdAfx.h"
#include ".\binarizationfilter.h"

#include "Resource.h"

using namespace DShowLib;

extern HINSTANCE g_hInst;

CBinarizationFilter::CBinarizationFilter()
	:	m_bEnabled( false ),
		m_threshold( 127 )
{
	// Add 'enable' parameter to enable or disable the binarization
	addBoolParam( "enable", &CBinarizationFilter::getEnable, &CBinarizationFilter::setEnable );

	// Add 'threshold' parameter to set the binarization threshold
	addLongParam( "threshold", &CBinarizationFilter::getThreshold, &CBinarizationFilter::setThreshold );
}

/*
 *	This method returns filter information.
 *
 *	The presence of getStaticFilterInfo is required because
 *	we derived from FrameFilterImpl.
 *
 *	We do not need to fill the module path member, because it will be set
 *	by the filter loader.
 */
FilterInfo CBinarizationFilter::getStaticFilterInfo()
{
	// Return a filter name and declare the filter as eFC_GENERIC.
	FilterInfo fi = { L"Demo_Binarization", L"", eFC_GENERIC };
	return fi;
}

/*
 *	This method fills the FrameTypeInfoArray arr with the frame types this filter
 *	accepts as input.
 *
 *	For the binarization filter, only the gray color formats eY800 and eRGB8 are accepted.
 */
void CBinarizationFilter::getSupportedInputTypes( DShowLib::FrameTypeInfoArray& arr ) const
{
	// This filter works for 8-bit-gray images only
	arr.push_back( eRGB8 );
	arr.push_back( eY800 );
}

/*
 *	This method returns the output frame type for a given input frame type.
 *
 *	The binarization filter does not change size or color format,
 *	so the only output frame type is the input frame type.
 */
bool CBinarizationFilter::getTransformOutputTypes( const DShowLib::FrameTypeInfo& in_type,
												   DShowLib::FrameTypeInfoArray& out_types ) const
{
	// We don't change the image type, output = input
	out_types.push_back( in_type );

	return true;
}

/*
 *	This method is called to copy image data from the src frame to the dest frame.
 *
 *	Depending on the value of m_bEnabled, this implementation applies a binarization or
 *	copies the image data without modifying it.
 */
bool CBinarizationFilter::transform( const DShowLib::IFrame& src, DShowLib::IFrame& dest )
{
	// Check whether the destination frame is available
	if( dest.getPtr() == 0 ) return false;

	BYTE* pIn = src.getPtr();
	BYTE* pOut = dest.getPtr();

	// Copy the member variables to the function's stack, to protect them from being
	// overwritten by parallel calls to setThreshold() etc.
	//
	// beginParamTransfer/endParamTransfer makes sure that the values from various
	// member variables are consistent, because the user of this filter must enclose
	// writing parameter access into beginParamTransfer/endParamTransfer, too.
	beginParamTransfer();
	bool enabled = m_bEnabled;
	int threshold = m_threshold;
	endParamTransfer();

	// Check whether binarization is enabled
	if( m_bEnabled )
	{
		// For each byte in the input buffer, check whether it is greater or
		// equal to the threshold.
		int bufferSize = src.getFrameType().buffersize;
		while( bufferSize-- > 0 )
		{
			if( *pIn++ >= threshold )
			{
				*pOut++ = 255;
			}
			else
			{
				*pOut++ = 0;
			}
		}
	}
	else
	{
		// Binarization is disabled: Copy the image data without modifying it.
		memcpy( pOut, pIn, src.getFrameType().buffersize );
	}

	return true;
}

/*
 *	Returns the 'enabled' state of the binarization
 */
tFilterError CBinarizationFilter::getEnable( bool& bEnable )
{
	bEnable = m_bEnabled;
	return eNO_ERROR;
}

/*
 *	Sets the 'enabled' state of the binarization
 */
tFilterError CBinarizationFilter::setEnable( bool bEnable )
{
	m_bEnabled = bEnable;
	return eNO_ERROR;
}

/*
 *	Returns the binarization threshold
 */
tFilterError CBinarizationFilter::getThreshold( long& threshold )
{
	threshold = m_threshold;
	return eNO_ERROR;
}

/*
 *	Sets the binarization threshold
 */
tFilterError CBinarizationFilter::setThreshold( long threshold )
{
	m_threshold = threshold;
	return eNO_ERROR;
}

/*
 *	This method is called to check whether this filter has a dialog.
 *
 *	We return true, because he have one.
 */
bool	CBinarizationFilter::hasDialog() const
{
	return true;
}

/*
 *	Dialog procedure
 */
INT_PTR CALLBACK BinarizationConfigDlgProc( HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	// In the lParam of the WM_INITIDIALOG message the pointer to the
	// filter instance was stored by callDialog.
	if( uMsg == WM_INITDIALOG )
	{
		// Save the pointer in the window user data.
		::SetWindowLong( hwndDlg, GWL_USERDATA, (long)lParam );
	}

	// Retrieve the pointer from the window user daat.
	CBinarizationFilter* pDlg = (CBinarizationFilter*)(LONG_PTR)::GetWindowLong( hwndDlg, GWL_USERDATA );

	// Call the dialog proc of the filter class
	if( pDlg )
	{
		return pDlg->DlgProc( hwndDlg, uMsg, wParam, lParam );
	}
	else
	{
		return 0;
	}
}

/*
 *	Display dialog box
 */
bool	CBinarizationFilter::callDialog( HWND hParent )
{
	// Save settings
	std::string data = getSettings();

	// Display modal dialog.
	// Pass the pointer to this instance to WM_INITDIALOG.
	INT_PTR result = DialogBoxParam( g_hInst,
									MAKEINTRESOURCE(IDD_BINARIZATION_CONFIG),
									hParent,
									BinarizationConfigDlgProc,
									(LPARAM)this );

	// When the user clicked 'cancel' restore settings
	if( result == IDCANCEL )
	{
		setSettings( data );
	}

	// Return true when the dialog was displayed.
	return result >= 1;
}

/*
 *	Dialog procedure implementation
 *
 *	Handles button and scroll messages
 */
INT_PTR	CBinarizationFilter::DlgProc( HWND hWndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	switch( uMsg )
	{
	case WM_INITDIALOG:
		{
			HWND hEnabled = ::GetDlgItem( hWndDlg, IDC_ENABLE );
			::SendMessage( hEnabled, BM_SETCHECK, m_bEnabled ? BST_CHECKED : BST_UNCHECKED, 0 );

			HWND hThreshold = ::GetDlgItem( hWndDlg, IDC_THRESHOLD );
			::SendMessage( hThreshold, TBM_SETRANGE, TRUE, (LPARAM)MAKELONG(0,255) );
			::SendMessage( hThreshold, TBM_SETPOS, TRUE, m_threshold );
			::EnableWindow( hThreshold, m_bEnabled ? TRUE : FALSE );

			HWND hhThresholdStatic = ::GetDlgItem( hWndDlg, IDC_THRESHOLD_STATIC );
			char buf[20];
			itoa( m_threshold, buf, 10 );
			::SetWindowText( hhThresholdStatic, buf );
			::EnableWindow( hhThresholdStatic, m_bEnabled ? TRUE : FALSE );
		}
		break;

	case WM_COMMAND:
		{
			switch( HIWORD(wParam) )
			{
			case BN_CLICKED:
				switch( LOWORD(wParam) )
				{
				case IDOK:
					::EndDialog( hWndDlg, IDOK );
					return 0;
				case IDCANCEL:
					::EndDialog( hWndDlg, IDCANCEL );
					return 0;
				case IDC_ENABLE:
					{
						HWND hEnabled = ::GetDlgItem( hWndDlg, IDC_ENABLE );
						bool bEnabled = ::SendMessage( hEnabled, BM_GETCHECK, 0, 0 ) == BST_CHECKED;

						beginParamTransfer();
						setParameter( "enable", bEnabled );
						endParamTransfer();

						HWND hThreshold = ::GetDlgItem( hWndDlg, IDC_THRESHOLD );
						::EnableWindow( hThreshold, bEnabled ? TRUE : FALSE );
						HWND hhThresholdStatic = ::GetDlgItem( hWndDlg, IDC_THRESHOLD_STATIC );
						::EnableWindow( hhThresholdStatic, bEnabled ? TRUE : FALSE );
					}
					return 0;
				}
				break;
			}
		}
		break;
	case WM_HSCROLL:
		{
			HWND hSlider = (HWND)lParam;
			int threshold = (int)::SendMessage( hSlider, TBM_GETPOS, 0, 0 );

			beginParamTransfer();
			setParameter( "threshold", threshold );
			endParamTransfer();

			char buf[20];
			itoa( threshold, buf, 10 );
			::SetWindowText( ::GetDlgItem( hWndDlg, IDC_THRESHOLD_STATIC ), buf );
		}
		break;
	}	
	return 0;
}