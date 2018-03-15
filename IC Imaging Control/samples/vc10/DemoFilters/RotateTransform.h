
#ifndef _ROTATETRANSFORM_H_INC_
#define _ROTATETRANSFORM_H_INC_

#include <tisudshl.h>
#include "FrameFilterImpl.h"

class CRotateTransform
	:	public DShowLib::FrameFilterImpl<CRotateTransform>
{
public:
	CRotateTransform();

	static DShowLib::FilterInfo		getStaticFilterInfo();

	DShowLib::tFilterError	setAngle( float val );
	DShowLib::tFilterError	getAngle( float& val );

	virtual void	getSupportedInputTypes( _DSHOWLIB_NAMESPACE::FrameTypeInfoArray& arr ) const;
	virtual bool	getTransformOutputTypes( const _DSHOWLIB_NAMESPACE::FrameTypeInfo& in_type, _DSHOWLIB_NAMESPACE::FrameTypeInfoArray& out_types ) const;
	virtual bool	transform( const _DSHOWLIB_NAMESPACE::IFrame& src, _DSHOWLIB_NAMESPACE::IFrame& dest );

	virtual bool	hasDialog() const;
	virtual bool	callDialog( HWND hparent );

	INT_PTR			DlgProc( HWND hWndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam );

private:
	float		m_Angle;
};

#endif // _ROTATETRANSFORM_H_INC_
