
#ifndef _SNAPFILTER_H_INC_
#define _SNAPFILTER_H_INC_

#include "FrameImpl.h"

class CSnapFilter
	:	public DShowLib::FrameUpdateFilterImpl<CSnapFilter>
{

public:
	CSnapFilter();

	static DShowLib::FilterInfo getStaticFilterInfo();

protected:
	virtual void    getSupportedInputTypes( DShowLib::FrameTypeInfoArray& arr ) const ;
	virtual bool    updateInPlace( DShowLib::IFrame& src );

	virtual void	notifyStart( const DShowLib::FrameTypeInfo& in_type );
	virtual void	notifyStop();

	virtual bool    hasDialog() const;
	virtual bool	callDialog( HWND hParent );

private:
	smart_ptr<CFrameImpl>	m_pBuffer;
	bool					m_bDoSnap;
	HANDLE					m_hEvent;
	bool					m_bLiveVideoRunning;

	bool snapImage( const std::string& szFileName );

	DShowLib::tFilterError doSave( _bstr_t Value );
	DShowLib::tFilterError dummyGetSave( _bstr_t &Value );

	DShowLib::tFilterError doSnap( bool bSnap );
	DShowLib::tFilterError dummyGetSnap( bool& bSnap );

};

#endif
