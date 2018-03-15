
#include "stdafx.h"
#include "DeNoiseTransform.h"

#include "resource.h"

using namespace _DSHOWLIB_NAMESPACE;

extern HINSTANCE g_hInst;

CDeNoiseTransform::CDeNoiseTransform()
	:	m_frames( 2 ),
		m_pData( 0 ),
		m_frameCount( 0 ),
		m_bRunning( false )
{
	addLongParam( L"buffer count", &CDeNoiseTransform::getBufferCount, &CDeNoiseTransform::setBufferCount );
}

CDeNoiseTransform::~CDeNoiseTransform()
{
	delete[] m_pData;
}

FilterInfo		CDeNoiseTransform::getStaticFilterInfo()
{
	static FilterInfo f = { L"Demo_DeNoise", L"", eFC_GENERIC };
	return f;
}

tFilterError	CDeNoiseTransform::setBufferCount( long val )
{
	if( m_bRunning )		return eINVALID_FILTER_STATE;

	m_frames = val;

	return eNO_ERROR;
}

tFilterError	CDeNoiseTransform::getBufferCount( long& val )
{
	val = m_frames;
	return eNO_ERROR;
}

void	CDeNoiseTransform::getSupportedInputTypes( FrameTypeInfoArray& arr ) const
{
	arr.addFrameType( eRGB8 );
	arr.addFrameType( eY800 );
	arr.addFrameType( eRGB24 );
	arr.addFrameType( eRGB32 );
}

void	CDeNoiseTransform::notifyStop()
{
	m_bRunning = false;
	delete[] m_pData;
	m_pData = 0;
}

bool	CDeNoiseTransform::getTransformOutputTypes( const FrameTypeInfo& in_type, FrameTypeInfoArray& out_types ) const
{
	out_types.push_back( in_type );
	return true;
}

void	CDeNoiseTransform::notifyStart( const FrameTypeInfo& in_type, const FrameTypeInfo& out_type )
{
	m_frameCount = 0;
	if( !m_pData || in_type != m_DataFrameType )
	{
		delete[] m_pData;
		m_pData = new short[ in_type.buffersize ];
		m_DataFrameType = in_type;
	}
	m_bRunning = true;
}

bool	CDeNoiseTransform::transform( const IFrame& src, IFrame& dest )
{
	bool rval = false;

	if( dest.getPtr() == 0 )			return false;

	assert( m_pData != 0 && dest.getFrameType() == m_DataFrameType );

	unsigned int bufferSize = src.getFrameType().buffersize;
	if( m_frameCount == 0 )
	{
		ZeroMemory( m_pData, bufferSize * sizeof( short ) );
	}

	beginParamTransfer();

	BYTE* pInput = src.getPtr();
	if( ++m_frameCount >= (1 << m_frames) )
	{
		BYTE* pOutput = dest.getPtr();
		for( unsigned int i = 0; i < bufferSize; ++i )
		{
			BYTE b = (m_pData[i] + pInput[i]) >> m_frames;
			pOutput[i] = b;
		}

		m_frameCount = 0;
		rval = true;
	}
	else
	{
		for( unsigned int i = 0; i < bufferSize; ++i )
		{
			m_pData[i] += pInput[i];
		}
	}

	endParamTransfer();

	return rval;
}


bool	CDeNoiseTransform::hasDialog() const
{
	return true;
}

INT_PTR CALLBACK DeNoiseConfigDlgProc( HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	if( uMsg == WM_INITDIALOG )
	{
		::SetWindowLong( hwndDlg, GWL_USERDATA, (long)lParam );
	}

	CDeNoiseTransform* pDlg = (CDeNoiseTransform*)(LONG_PTR)::GetWindowLong( hwndDlg, GWL_USERDATA );

	if( pDlg )
	{
		return pDlg->DlgProc( hwndDlg, uMsg, wParam, lParam );
	}
	else
	{
		return 0;
	}
}

bool	CDeNoiseTransform::callDialog( HWND hParent )
{
	std::string data = getSettings();

	INT_PTR result = DialogBoxParam( g_hInst, MAKEINTRESOURCE(IDD_DENOISE_CONFIG), hParent, DeNoiseConfigDlgProc, (LPARAM)this );

	if( result == IDCANCEL )
	{
		setSettings( data );
	}

	return result >= 1;
}

INT_PTR	CDeNoiseTransform::DlgProc( HWND hWndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	switch( uMsg )
	{
	case WM_INITDIALOG:
		{
			HWND hDeNoise = ::GetDlgItem( hWndDlg, IDC_DENOISE );
			::SendMessage( hDeNoise, TBM_SETRANGE, TRUE, (LPARAM)MAKELONG(0,5) );
			::SendMessage( hDeNoise, TBM_SETPOS, TRUE, m_frames );

			char buf[20];
			itoa( int( pow( (float)2, m_frames ) ), buf, 10 );
			::SetWindowText( ::GetDlgItem( hWndDlg, IDC_DENOISE_STATIC ), buf );
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
				}
				break;
			}
		}
		break;
	case WM_HSCROLL:
		{
			HWND hSlider = (HWND)lParam;
			beginParamTransfer();
			m_frames = (int)::SendMessage( hSlider, TBM_GETPOS, 0, 0 );
			m_frameCount = 0;
			char buf[20];
			itoa( int( pow( (float)2, m_frames ) ), buf, 10 );
			::SetWindowText( ::GetDlgItem( hWndDlg, IDC_DENOISE_STATIC ), buf );
			endParamTransfer();
		}
		break;
	}	
	return 0;
}