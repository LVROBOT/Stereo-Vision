
#include "stdafx.h"
#include "RotateTransform.h"

#include "Resource.h"

using namespace DShowLib;

extern HINSTANCE g_hInst;

CRotateTransform::CRotateTransform()
	:	m_Angle( 0.0f )
{
	addFloatParam( "angle", &CRotateTransform::getAngle, &CRotateTransform::setAngle );
}

FilterInfo		CRotateTransform::getStaticFilterInfo()
{
	static FilterInfo f = { L"Demo_Rotation", L"", eFC_GENERIC };
	return f;
}

tFilterError	CRotateTransform::setAngle( float val )
{
	m_Angle = val;
	return eNO_ERROR;
}
tFilterError	CRotateTransform::getAngle( float& val )
{
	val = m_Angle;
	return eNO_ERROR;
}

void	CRotateTransform::getSupportedInputTypes( FrameTypeInfoArray& arr ) const
{
	arr.addFrameType( _DSHOWLIB_NAMESPACE::eRGB8 );
	arr.addFrameType( _DSHOWLIB_NAMESPACE::eY800 );
	arr.addFrameType( _DSHOWLIB_NAMESPACE::eRGB24 );
	arr.addFrameType( _DSHOWLIB_NAMESPACE::eRGB32 );
}

bool	CRotateTransform::getTransformOutputTypes( const FrameTypeInfo& in_type, FrameTypeInfoArray& out_types ) const
{
	_DSHOWLIB_NAMESPACE::FrameTypeInfo out_type = in_type;

	// Output image width and height have to be the length of the diagonal of the source image
	out_type.dim.cx = (int)(sqrt( (float)(in_type.dim.cx * in_type.dim.cx + in_type.dim.cy * in_type.dim.cy) ) + 0.5f);
	out_type.dim.cy = out_type.dim.cx;

	out_type.buffersize = calcRequiredBuffersize( out_type );

	out_types.push_back( out_type );
	return true;
}

bool	CRotateTransform::transform( const IFrame& src, IFrame& dest )
{
	if( dest.getPtr() == 0 )	return false;

	float sina = sin( m_Angle );
	float cosa = cos( m_Angle );

	BYTE* pSrcBasePtr = src.getPtr();
	BYTE* pDestPtr = dest.getPtr();

	int srcDimx = src.getFrameType().dim.cx;
	int srcDimy = src.getFrameType().dim.cy;
	int destDimx = dest.getFrameType().dim.cx;
	int destDimy = dest.getFrameType().dim.cy;

	int mdx = destDimx / 2;
	int mdy = destDimy / 2;

	int msx = srcDimx / 2;
	int msy = srcDimy / 2;

	int bytesperpixel = src.getFrameType().getBitsPerPixel() / 8;

	// For each pixel in the destination image...
	for( int y = 0; y < destDimy; ++y )
	{
		for( int x = 0; x < destDimx; ++x )
		{
			// Find the corresponding pixel in the source image by rotation in reverse direction
			// around the middle of the image
			int dx = x - mdx;
			int dy = y - mdy;

			float ndx = dx * cosa - dy * sina;
			float ndy = dx * sina + dy * cosa;

			int sx = (int)(msx + ndx);
			int sy = (int)(msy + ndy);

			// Check whether the source pixel is inside the source image area
			if( sx < 0 || sx >= srcDimx || sy < 0 || sy >= srcDimy )
			{
				// Outside: Fill with zeros
				for( int i = 0; i < bytesperpixel; ++i )
				{
					*pDestPtr++ = 0;
				}
			}
			else
			{
				// Inside: Copy pixel data
				for( int i = 0; i < bytesperpixel; ++i )
				{
					*pDestPtr++ = pSrcBasePtr[ sx * bytesperpixel + sy * bytesperpixel * srcDimx + i ];
				}
			}
		}
	}

	return true;
}

bool	CRotateTransform::hasDialog() const
{
	return true;
}

INT_PTR CALLBACK RotationConfigDlgProc( HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	if( uMsg == WM_INITDIALOG )
	{
		::SetWindowLong( hwndDlg, GWL_USERDATA, (long)lParam );
	}

	CRotateTransform* pDlg = (CRotateTransform*)(LONG_PTR)::GetWindowLong( hwndDlg, GWL_USERDATA );

	if( pDlg )
	{
		return pDlg->DlgProc( hwndDlg, uMsg, wParam, lParam );
	}
	else
	{
		return 0;
	}
}

bool	CRotateTransform::callDialog( HWND hParent )
{
	std::string data = getSettings();

	INT_PTR result = DialogBoxParam( g_hInst, MAKEINTRESOURCE(IDD_ROTATION_CONFIG), hParent, RotationConfigDlgProc, (LPARAM)this );

	if( result == IDCANCEL )
	{
		setSettings( data );
	}

	return result >= 1;
}

INT_PTR		CRotateTransform::DlgProc( HWND hWndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	switch( uMsg )
	{
	case WM_INITDIALOG:
		{
			HWND hDeNoise = ::GetDlgItem( hWndDlg, IDC_ANGLE_SLIDER );
			::SendMessage( hDeNoise, TBM_SETRANGE, TRUE, (LPARAM)MAKELONG(0,360) );

			int a = int( m_Angle * 180.0f / M_PI );
			::SendMessage( hDeNoise, TBM_SETPOS, TRUE, a );

			char buf[20];
			itoa( a, buf, 10 );
			::SetWindowText( ::GetDlgItem( hWndDlg, IDC_ANGLE_STATIC ), buf );
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

			int a = (int)::SendMessage( hSlider, TBM_GETPOS, 0, 0 );

			m_Angle = float(a / 180.0 * M_PI);

			char buf[20];
			itoa( a, buf, 10 );
			::SetWindowText( ::GetDlgItem( hWndDlg, IDC_ANGLE_STATIC ), buf );
		}
	}	
	return 0;
}