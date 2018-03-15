
#include "stdafx.h"
#include "Dialogs.h"
#include "Resource.h"

using namespace _DSHOWLIB_NAMESPACE;

#include "MediaStreamSinkDialogData.h"

// from Dialogs.cpp
extern HANDLE hDllModule;

inline CMediaStreamSinkDialogData* getDialogData( HWND hwndDlg )
{
	LONG_PTR pData = ::GetWindowLongPtr( hwndDlg, DWLP_USER );
	assert( pData );
	return reinterpret_cast<CMediaStreamSinkDialogData*>( pData );
}

void	updateComboBox( HWND hCbx, const std::vector<std::wstring>& vec, int curidx, bool bEnabled = true )
{
	LRESULT res = ::SendMessage( hCbx, CB_RESETCONTENT, 0, 0 );
	if( vec.empty() )
	{
		EnableWindow( hCbx, false );
		res = ::SendMessage( hCbx, CB_ADDSTRING, 0, (LPARAM)TEXT("n/a") );
		::SendMessage( hCbx, CB_SETCURSEL, (WPARAM) 0, 0 );
	}
	else
	{
		EnableWindow( hCbx, bEnabled );
		for( std::vector<std::wstring>::const_iterator i = vec.begin(); i != vec.end(); ++i )
		{
			res = ::SendMessage( hCbx, CB_ADDSTRING, 0, (LPARAM)i->c_str() );
		}
		if( curidx >= 0 )
		{
			::SendMessage( hCbx, CB_SETCURSEL, (WPARAM) curidx, 0 );
		}
	}
}

void	updateCheck( HWND hCB, bool bCurVal, bool bAvailable = true )
{
	::EnableWindow( hCB, bAvailable );
	if( bAvailable )
	{
		::SendMessage( hCB, BM_SETCHECK, bCurVal ? BST_CHECKED : BST_UNCHECKED, 0 );
	}
	else
	{
		::SendMessage( hCB, BM_SETCHECK, BST_UNCHECKED, 0 );
	}
}

int		getComboSelection( HWND hDlg, UINT comboID )
{
	HWND hCB = GetDlgItem( hDlg, comboID );
	return (int)::SendMessage( hCB, CB_GETCURSEL, 0, 0 );
}


void updateDialog( HWND hwndDlg, CMediaStreamSinkDialogData* pData )
{
	tContentType containerType = pData->getSelectedContainerType();

	HWND hWndContainerCombo = ::GetDlgItem( hwndDlg, IDC_CONTAINER_COMBO );
	updateComboBox( hWndContainerCombo, pData->getContainerList(),
		pData->getSelectedContainerIndex() );

	HWND hWndCodecCombo = ::GetDlgItem( hwndDlg, IDC_CODEC_COMBO );
	updateComboBox( hWndCodecCombo, pData->getCompressorList(),
		pData->getSelectedCodecIndex(),
		containerType == eCodec && pData->isCustomCodecSupported() );

	HWND hWndUncompressedCombo = ::GetDlgItem( hwndDlg, IDC_UNCOMPRESSED_COMBO );
	updateComboBox( hWndUncompressedCombo, pData->getUncompressedList(),
		pData->getSelectedUncompressedIndex(), 
		containerType == eUncompressed && pData->isCustomCodecSupported() );

	HWND hWndRadioCodec = ::GetDlgItem( hwndDlg, IDC_CODEC_RADIO );
	HWND hWndRadioUncompressed = ::GetDlgItem( hwndDlg, IDC_UNCOMPRESSED_RADIO );
	HWND hWndRadioUnspecified = ::GetDlgItem( hwndDlg, IDC_UNSPECIFIED_RADIO );
	HWND hCodecPropsButton = ::GetDlgItem( hwndDlg, IDC_CODEC_PROPERTIES );

	switch( pData->getSelectedContainerType() )
	{
	case eCodec:
		updateCheck( hWndRadioCodec, true, pData->isCustomCodecSupported() );
		updateCheck( hWndRadioUncompressed, false, pData->isCustomCodecSupported() );
		updateCheck( hWndRadioUnspecified, false );

		::EnableWindow( hCodecPropsButton, pData->selectedCodecHasDialog() );
		break;
	case eUncompressed:
		updateCheck( hWndRadioCodec, false, pData->isCustomCodecSupported() );
		updateCheck( hWndRadioUncompressed, true, pData->isCustomCodecSupported() );
		updateCheck( hWndRadioUnspecified, false );

		::EnableWindow( hCodecPropsButton, false );
		break;
	case eUnspecified:
		updateCheck( hWndRadioCodec, false, pData->isCustomCodecSupported() );
		updateCheck( hWndRadioUncompressed, false, pData->isCustomCodecSupported() );
		updateCheck( hWndRadioUnspecified, true );

		::EnableWindow( hCodecPropsButton, false );
		break;
	}

	::SetDlgItemText( hwndDlg, IDC_FILENAME_EDIT, pData->getFilename().c_str() );
}


INT_PTR CALLBACK MediaStreamSinkDialogProc( HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	BOOL rval = FALSE;
	switch( uMsg )
	{
	case WM_CLOSE:
		{
			EndDialog( hwndDlg, IDCANCEL );
			rval = TRUE;
			break;
		}
	case WM_INITDIALOG:
		{
			// register pointer to the window msg receiver
			::SetWindowLongPtr( hwndDlg, DWLP_USER, (LONG_PTR)lParam );
			CMediaStreamSinkDialogData* pData = getDialogData( hwndDlg );

			updateDialog( hwndDlg, pData );

			break;
		}
	case WM_COMMAND:
		{
			CMediaStreamSinkDialogData* pData = getDialogData( hwndDlg );

			WORD notifyMsg = HIWORD(wParam);
			switch( LOWORD( wParam ) )
			{
			case IDOK:
				if( notifyMsg == BN_CLICKED )
				{
					EndDialog( hwndDlg, IDOK );
					rval = TRUE;
				}
				break;
			case IDCANCEL:
				{
					EndDialog( hwndDlg, IDCANCEL );
					rval = TRUE;
				}
			case IDC_CODEC_RADIO:
				{
					pData->selectContainerType( eCodec );
					updateDialog( hwndDlg, pData );
				}
				break;
			case IDC_UNCOMPRESSED_RADIO:
				{
					pData->selectContainerType( eUncompressed );
					updateDialog( hwndDlg, pData );
				}
				break;
			case IDC_UNSPECIFIED_RADIO:
				{
					pData->selectContainerType( eUnspecified );
					updateDialog( hwndDlg, pData );
				}
				break;
			case IDC_CONTAINER_COMBO:
				if( notifyMsg == CBN_SELCHANGE )
				{
					pData->selectContainer( getComboSelection( hwndDlg, IDC_CONTAINER_COMBO ) );
					updateDialog( hwndDlg, pData );
				}
				break;
			case IDC_CODEC_COMBO:
				if( notifyMsg == CBN_SELCHANGE )
				{
					pData->selectCodec( getComboSelection( hwndDlg, IDC_CODEC_COMBO ) );
					updateDialog( hwndDlg, pData );
				}
				break;
			case IDC_UNCOMPRESSED_COMBO:
				if( notifyMsg == CBN_SELCHANGE )
				{
					pData->selectUncompressed( getComboSelection( hwndDlg, IDC_UNCOMPRESSED_COMBO ) );
					updateDialog( hwndDlg, pData );
				}
				break;
			case IDC_CODEC_PROPERTIES:
				{
					pData->callCodecDialog( hwndDlg );
				}
				break;
			case IDC_FILENAME_EDIT:
				if( notifyMsg == EN_CHANGE )
				{
					TCHAR txt[MAX_PATH];
					::GetDlgItemText( hwndDlg, IDC_FILENAME_EDIT, txt, MAX_PATH );
					pData->setFilename( txt );
				}
				break;
			case IDC_FILENAME_BUTTON:
				{
					OPENFILENAME ofn;
					ZeroMemory( &ofn, sizeof( OPENFILENAME ) );
					ofn.lStructSize = sizeof( OPENFILENAME );
					ofn.hwndOwner = hwndDlg;

					std::wstring ext = pData->getPreferredFilenameExtension();
					std::wstring filter = L"Video Files (*." + ext + L")|*." + ext + L"||";
					for( unsigned int i = 0; i < filter.length(); ++i )
						if( filter[i] == L'|' ) filter[i] = L'\0';
					ofn.lpstrFilter = filter.c_str();
					ofn.lpstrDefExt = ext.c_str();

					TCHAR buf[MAX_PATH] = { 0 };
					ofn.lpstrFile = buf;
					ofn.nMaxFile = MAX_PATH;
					ofn.Flags = OFN_ENABLESIZING;

					if( ::GetSaveFileName( &ofn ) )
					{
						::SetDlgItemText( hwndDlg, IDC_FILENAME_EDIT, ofn.lpstrFile  );
						pData->setFilename( ofn.lpstrFile );
					}
				}
				break;
			}

			break;
		}
	}

	return rval;
}

DIALOGS_API smart_ptr<MediaStreamSink> showMediaStreamSinkDialog( smart_ptr<_DSHOWLIB_NAMESPACE::GrabberSinkType> pOldSink, HWND hParent )
{
	if( !hParent )
	{
		hParent = ::GetActiveWindow();
	}

	CMediaStreamSinkDialogData fwsData( pOldSink );

	INT_PTR dlg_ret = ::DialogBoxParam( (HINSTANCE)hDllModule, MAKEINTRESOURCE(IDD_VIDEOFILE_DIALOG), 
		hParent, MediaStreamSinkDialogProc, (LPARAM)&fwsData );

	if( dlg_ret == IDOK )
	{
		return fwsData.createSink();
	}
	else
	{
		return 0;
	}
}