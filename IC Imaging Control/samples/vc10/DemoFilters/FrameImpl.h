
#ifndef FRAMEIMPL_H_INC
#define FRAMEIMPL_H_INC

class CFrameImpl
	:	public DShowLib::IFrame
{
public:
	CFrameImpl( DShowLib::IFrame& frame );
	~CFrameImpl();

	virtual const DShowLib::FrameTypeInfo&		getFrameType() const;
	virtual BYTE*								getPtr() const;
	virtual const DShowLib::tsMediaSampleDesc&	getSampleDesc() const;

	virtual bool                        getMediaSampleInfo_( void* buffer, int buffer_len, int& data_available ) const
	{
		return false;
	}

private:
	DShowLib::FrameTypeInfo	m_fti;
	DShowLib::tsMediaSampleDesc	m_MediaSampleDesc;

	std::vector<BYTE>			data_;
};

#endif
