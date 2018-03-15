#include "StdAfx.h"
#include ".\binarizationfilter.h"

using namespace DShowLib;

CBinarizationFilter::CBinarizationFilter()
	:	m_bEnabled( false ),
		m_threshold( 127 )
{
}

/*
 *	This method returns filter information.
 *	This is not really needed here, because the filter will never be loaded from a .ftf file.
 *
 *	However, the presence of getStaticFilterInfo is required because
 *	we derived from FrameFilterImpl.
 */
FilterInfo CBinarizationFilter::getStaticFilterInfo()
{
	// Return a filter name and declare the filter as eFC_INTERNAL.
	FilterInfo fi = { L"Binarization", L"", eFC_INTERNAL };
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
 *	Enables or disables the binarization.
 *
 *	Only call this method in a beginParamTransfer/endParamTransfer block.
 */
void CBinarizationFilter::enable( bool bEnable )
{
	m_bEnabled = bEnable;
}

/*
 *	Sets disables the binarization threshold.
 *
 *	Only call this method in a beginParamTransfer/endParamTransfer block.
 */
void CBinarizationFilter::setThreshold( int th )
{
	m_threshold = th;
}
