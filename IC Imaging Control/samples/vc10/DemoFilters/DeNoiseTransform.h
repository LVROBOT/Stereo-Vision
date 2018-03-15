
#ifndef DENOISETRANSFORM_H_INC_
#define DENOISETRANSFORM_H_INC_

/** This filter implements a DeNoise filter, which reduces the noise in the image by
	* adding n frames up, and then after n calls delivers the resulting image.
	*/
class CDeNoiseTransform
	:	public DShowLib::FrameFilterImpl<CDeNoiseTransform>
{
	bool				m_bRunning;
	int					m_frames;
	short*				m_pData;
	DShowLib::FrameTypeInfo	m_DataFrameType;

	int					m_frameCount;

public:
	CDeNoiseTransform();
	~CDeNoiseTransform();

	static DShowLib::FilterInfo		getStaticFilterInfo();

	DShowLib::tFilterError	setBufferCount( long val );
	DShowLib::tFilterError	getBufferCount( long& val );

	virtual bool	hasDialog() const;
	virtual bool	callDialog( HWND hParent );

	INT_PTR	DlgProc( HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam );

protected:

	virtual void	getSupportedInputTypes( DShowLib::FrameTypeInfoArray& arr ) const;
	virtual bool	getTransformOutputTypes( const DShowLib::FrameTypeInfo& in_type, DShowLib::FrameTypeInfoArray& out_types ) const;

	virtual void	notifyStart( const DShowLib::FrameTypeInfo& in_type, const DShowLib::FrameTypeInfo& out_type );
	virtual void	notifyStop();

	virtual bool	transform( const DShowLib::IFrame& src, DShowLib::IFrame& dest );
};

#endif // DENOISETRANSFORM_H_INC_
