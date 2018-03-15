
#include "stdafx.h"
#include "Dialogs.h"
#include "Resource.h"

#include "VideoCaptureDialogData.h"

// from Dialogs.cpp
extern HANDLE hDllModule;

using namespace _DSHOWLIB_NAMESPACE;

const int TIMER_UPDATE_TIME = 1;

inline CVideoCaptureDialogData* getDialogData( HWND hwndDlg )
{
	LONG_PTR pData = ::GetWindowLongPtr( hwndDlg, DWLP_USER );
	assert( pData );
	return reinterpret_cast<CVideoCaptureDialogData*>( pData );
}

void updateVideoCaptureDialog( HWND hwndDlg, CVideoCaptureDialogData* pData )
{
	::EnableWindow( ::GetDlgItem( hwndDlg, IDOK ), !pData->isRecording() );
	::EnableWindow( ::GetDlgItem( hwndDlg, IDC_START_BUTTON ), !pData->isRecording() );
	::EnableWindow( ::GetDlgItem( hwndDlg, IDC_FILENAME_EDIT ), !pData->isRecording() );
	::EnableWindow( ::GetDlgItem( hwndDlg, IDC_FILENAME_BUTTON ), !pData->isRecording() );
	::EnableWindow( ::GetDlgItem( hwndDlg, IDC_STOP_BUTTON ), pData->isRecording() );
	::SendMessage( ::GetDlgItem( hwndDlg, IDC_PAUSE_BUTTON ), BM_SETCHECK, pData->isPaused() ? BST_CHECKED : BST_UNCHECKED, 0 );

	::SetWindowText( ::GetDlgItem( hwndDlg, IDC_CONTAINER_STATIC ), pData->getContainer().c_str() );
	::SetWindowText( ::GetDlgItem( hwndDlg, IDC_CODEC_STATIC ), pData->getCodec().c_str() );
	::SetWindowText( ::GetDlgItem( hwndDlg, IDC_FILE_STATIC ), pData->getFilename().c_str() );

	::EnableWindow( ::GetDlgItem( hwndDlg, IDC_EDIT_SINK ), !pData->isRecording() );
}

INT_PTR CALLBACK VideoCaptureDialogProc( HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	switch( uMsg )
	{
	case WM_CLOSE:
		{
			CVideoCaptureDialogData* pData = getDialogData( hwndDlg );
			if( !pData->isRecording() )
			{
				::EndDialog( hwndDlg, IDCANCEL );				
			}
			return TRUE;
		}
	case WM_INITDIALOG:
		{
			::SetWindowLongPtr( hwndDlg, DWLP_USER, (LONG_PTR)lParam );
			CVideoCaptureDialogData* pData = getDialogData( hwndDlg );

			updateVideoCaptureDialog( hwndDlg, pData );

			return FALSE;
		}
	case WM_COMMAND:
		{
			CVideoCaptureDialogData* pData = getDialogData( hwndDlg );

			WORD notifyMsg = HIWORD(wParam);
			switch( LOWORD( wParam ) )
			{
			case IDOK:
				::EndDialog( hwndDlg, IDOK );
				return TRUE;

			case IDC_START_BUTTON:
				pData->start();
				::SetTimer( hwndDlg, TIMER_UPDATE_TIME, 100, 0 );
				updateVideoCaptureDialog( hwndDlg, pData );
				return TRUE;

			case IDC_PAUSE_BUTTON:
				pData->pause();				
				updateVideoCaptureDialog( hwndDlg, pData );
				return TRUE;

			case IDC_STOP_BUTTON:
				pData->stop();
				::KillTimer( hwndDlg, TIMER_UPDATE_TIME );
				updateVideoCaptureDialog( hwndDlg, pData );
				return TRUE;

			case IDC_EDIT_SINK:
				{
					smart_ptr<MediaStreamSink> pSink = showMediaStreamSinkDialog( pData->getSink(), hwndDlg );
					if( pSink != 0 )
					{
						pData->setSink( pSink );
					}
					updateVideoCaptureDialog( hwndDlg, pData );
					return TRUE;
				}
			}

			break;
		}
	case WM_TIMER:
		{
			CVideoCaptureDialogData* pData = getDialogData( hwndDlg );

			switch( wParam )
			{
			case TIMER_UPDATE_TIME:
				{
					::SetDlgItemText( hwndDlg, IDC_TIME, pData->getRecordedTimeString().c_str() );

					break;
				}
			}

			break;
		}
	}

	return 0;
}

void showVideoCaptureDialog( const CVideoCaptureDialogData& dlgData, HWND hParent = 0 )
{
	if( !hParent )
	{
		hParent = ::GetActiveWindow();
	}

	INT_PTR dlg_ret = ::DialogBoxParam( (HINSTANCE)hDllModule, MAKEINTRESOURCE(IDD_VIDEOCAPTURE_DIALOG), 
		hParent, VideoCaptureDialogProc, (LPARAM)&dlgData );
}

DIALOGS_API void showVideoCaptureDialog( Grabber& grabber, smart_ptr<tMediaStreamSinkDialogSettings>& pSettings, HWND hParent )
{
	CVideoCaptureDialogData vcdData( grabber, pSettings );

	showVideoCaptureDialog( vcdData, hParent );

	pSettings = vcdData.getDialogSettings();
}

DIALOGS_API void showVideoCaptureDialog( Grabber& grabber, HWND hParent )
{
	CVideoCaptureDialogData vcdData( grabber );

	showVideoCaptureDialog( vcdData, hParent );
}