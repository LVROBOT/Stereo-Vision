

#pragma once


/**
 *	This frame filter applies a binarization on the image data.
 *	If enabled, every gray value greater of equal to a specified threshold is changed to 
 *	the maximum gray value, every other gray value is changed to zero.
 *
 *	Allowed input types: Y800, RGB8
 *
 *	Output types: Y800, RGB8, the input type determines the output type.
 *
 *	Parameters:
 *		enable:	Use enable( bool bEnable ) to enable or disable binarization.
 *				If binarization is disabled, the image data is not modified.
 *		threshold:
 *				Use setThreshold( int th ) to set the threshold for the
 *				binarization.
 *
 */
class CBinarizationFilter
	:	public DShowLib::FrameFilterImpl<CBinarizationFilter>
{
public:
	CBinarizationFilter();

public:
	// FrameFilterImpl implementation
	static	DShowLib::FilterInfo getStaticFilterInfo();

public:
	// IFrameFilter implementation
	virtual	void getSupportedInputTypes( DShowLib::FrameTypeInfoArray& arr ) const;
	virtual	bool getTransformOutputTypes( const DShowLib::FrameTypeInfo& in_type,
										  DShowLib::FrameTypeInfoArray& out_types ) const;
	virtual	bool transform( const DShowLib::IFrame& src, DShowLib::IFrame& dest );

public:
	// Enables or disabled binarizarion
	void	enable( bool bEnable );
	// Sets the threshold for the binarization
	void	setThreshold( int th );

private:
	bool	m_bEnabled;
	int		m_threshold;
};
