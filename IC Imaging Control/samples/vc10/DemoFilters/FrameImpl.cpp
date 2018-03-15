
#include "stdafx.h"

#include "FrameImpl.h"

using namespace DShowLib;

CFrameImpl::CFrameImpl( IFrame& frame )
	:	m_fti( frame.getFrameType() ),
		data_( m_fti.buffersize ),
		m_MediaSampleDesc( frame.getSampleDesc() )
{
	memcpy( &data_[0], frame.getPtr(), m_fti.buffersize );
}

CFrameImpl::~CFrameImpl()
{
}

const FrameTypeInfo&		CFrameImpl::getFrameType() const
{
	return m_fti;
}

BYTE*						CFrameImpl::getPtr() const
{
	return const_cast<BYTE*>( &(data_[0]) );
}

const tsMediaSampleDesc&	CFrameImpl::getSampleDesc() const
{
	return m_MediaSampleDesc;
}
