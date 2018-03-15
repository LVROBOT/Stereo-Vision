
#include "stdafx.h"

#include "MediaStreamSinkDialogData.h"

#include "../Common/CmdHelper.h"

#include <Shlobj.h>

using namespace _DSHOWLIB_NAMESPACE;


struct tUncompressedFormat {
	GUID			id;
	const wchar_t*	pName;

	tUncompressedFormat( const GUID& guid, const wchar_t* name )
		:	id( guid ),
		pName( name )
	{
	}

	std::wstring toStringW() const
	{
		return pName;
	}
};

/* */
const tUncompressedFormat s_UncompressedFormatList[] = 
{
	tUncompressedFormat( MEDIASUBTYPE_RGB32, L"RGB32" ),
	tUncompressedFormat( MEDIASUBTYPE_RGB24, L"RGB24" ),
	tUncompressedFormat( MEDIASUBTYPE_RGB565, L"RGB565" ),
	tUncompressedFormat( MEDIASUBTYPE_RGB555, L"RGB555" ),
	tUncompressedFormat( _DSHOWLIB_NAMESPACE::MEDIASUBTYPE_Y800, L"Y800" ),
	tUncompressedFormat( MEDIASUBTYPE_UYVY, L"UYVY" ),
};

const unsigned int s_UncompressedFormatListCount = sizeof( s_UncompressedFormatList ) / sizeof( s_UncompressedFormatList[0] );



CMediaStreamSinkDialogData::CMediaStreamSinkDialogData( smart_ptr<GrabberSinkType> pOldSink )
{
	m_pContainerList = MediaStreamContainer::getAvailableMediaStreamContainers();
	if( m_pContainerList == 0 )
	{
		throw std::string("Unable to get a list of available MediaStreamContainers");
	}

	if( m_pContainerList->size() < 1 )
	{
		throw std::string("No MediaStreamContainers found");
	}

	m_pCodecList = Codec::getAvailableCodecs();
	if( m_pCodecList == 0 )
	{
		throw std::string("Unable to get a list of available Codecs");
	}

	if( m_pCodecList->size() < 1 )
	{
		throw std::string("No Codecs found");
	}

	if( (pOldSink != 0) && ((pOldSink->getSinkType() & eMEDIASTREAM_SINK) != 0) )
	{
		init( smart_ptr<MediaStreamSink>( pOldSink ) );
	}
	else
	{
		init( 0 );
	}
}

/**
 *	This function initializes the dialog data.
 *	If a pOldSink pointer is specified, the data is initialized from this sink's settings;
 *	otherwise, default values are used.
 *
 */
void	CMediaStreamSinkDialogData::init( smart_ptr<_DSHOWLIB_NAMESPACE::MediaStreamSink> pOldSink )
{
	if( pOldSink != 0 )
	{
		m_filterList = pOldSink->getFrameFilters();

		m_FileName = pOldSink->getFilenameW();

		m_selectedContainer = 0;
		GUID container = pOldSink->getContainer()->getMediaStreamContainerID();	
		for( unsigned int i = 0; i < m_pContainerList->size(); ++i )
			if( m_pContainerList->at(i)->getMediaStreamContainerID() == container )
				m_selectedContainer = i;

		// default is unspecified
		m_type = eUnspecified;

		m_selectedCodec = 0;
		smart_ptr<Codec> pCodec = pOldSink->getCodec();
		if( pCodec != 0 )
		{
			m_type = eCodec;
			std::string codecName = pCodec->toString();

			for( unsigned int i = 0; i < m_pCodecList->size(); ++i )
				if( m_pCodecList->at(i)->toString() == codecName )
					m_selectedCodec = i;
		}

		m_selectedUCFormat = 0;
		GUID uncompressed = pOldSink->getSubType();
		if( uncompressed != GUID_NULL )
		{
			m_type = eUncompressed;
			for( unsigned int i = 0; i < s_UncompressedFormatListCount; ++i )
				if( s_UncompressedFormatList[i].id == uncompressed )
					m_selectedUCFormat = i;
		}
	}
	else
	{
		m_selectedContainer = 0;
		m_selectedCodec = 0;
		m_selectedUCFormat = 0;
		m_type = eCodec;		

		std::wstring fn = L"video.";
		fn += getSelectedContainer()->getPreferredFileExtensionW();

		TCHAR szPath[MAX_PATH] = { 0 };
		if( ::SHGetSpecialFolderPath( 0, szPath, CSIDL_PERSONAL, TRUE ) ) 
		{
			::PathAppend( szPath, fn.c_str() );
			m_FileName = szPath;
		}
		else
		{
			m_FileName = fn.c_str();
		}
	}
}

smart_ptr<MediaStreamSink>	CMediaStreamSinkDialogData::createSink()
{			
	smart_ptr<MediaStreamSink> pSink = 0;
	switch( m_type )
	{
	case 0:
		pSink = MediaStreamSink::create( getSelectedContainer(), getSelectedCodec(), m_filterList );
		break;
	case 1:
		pSink = MediaStreamSink::create( getSelectedContainer(), getSelectedUCFormat(), m_filterList );
		break;
	case 2:
		pSink = MediaStreamSink::create( getSelectedContainer(), m_filterList );
		break;
	}

	if( pSink != 0 )
	{
		pSink->setFilename( m_FileName );
	}

	return pSink;
}

smart_ptr<Codec>	CMediaStreamSinkDialogData::getSelectedCodec()
{
	return m_pCodecList->at( m_selectedCodec );
}

smart_ptr<MediaStreamContainer>	CMediaStreamSinkDialogData::getSelectedContainer()
{
	return m_pContainerList->at( m_selectedContainer );
}

GUID	CMediaStreamSinkDialogData::getSelectedUCFormat()
{
	return s_UncompressedFormatList[m_selectedUCFormat].id;
}

std::wstring		CMediaStreamSinkDialogData::getSelectedUCFormatName()
{
	return s_UncompressedFormatList[m_selectedUCFormat].pName;
}

std::vector<std::wstring>	CMediaStreamSinkDialogData::getContainerList()
{
	return toStringArrayPtrListPtrW( m_pContainerList );
}

std::vector<std::wstring>	CMediaStreamSinkDialogData::getCompressorList()
{
	return toStringArrayPtrListPtrW( m_pCodecList );
}

std::vector<std::wstring>	CMediaStreamSinkDialogData::getUncompressedList()
{
	return toStringArrayW( &s_UncompressedFormatList[0], &s_UncompressedFormatList[s_UncompressedFormatListCount] );
}

int							CMediaStreamSinkDialogData::getSelectedContainerIndex()
{
	return m_selectedContainer;
}

int							CMediaStreamSinkDialogData::getSelectedCodecIndex()
{
	return m_selectedCodec;
}

int							CMediaStreamSinkDialogData::getSelectedUncompressedIndex()
{
	return m_selectedUCFormat;
}

tContentType				CMediaStreamSinkDialogData::getSelectedContainerType()
{
	return m_type;
}


void						CMediaStreamSinkDialogData::selectContainerType( tContentType type )
{
	m_type = type;
}

void						CMediaStreamSinkDialogData::selectContainer( int index )
{
	assert( index >= 0 && index < (int) m_pContainerList->size() );

	std::wstring oldExt = getSelectedContainer()->getPreferredFileExtensionW();	
	m_selectedContainer = index;
	std::wstring newExt = getSelectedContainer()->getPreferredFileExtensionW();

	size_t oldExtP = m_FileName.length()-oldExt.length();
    if( m_FileName.substr( oldExtP ) == oldExt )
	{
		m_FileName = m_FileName.substr( 0, oldExtP ) + newExt;
	}

	if( !isCustomCodecSupported() )
	{
		selectContainerType( eUnspecified );
	}
}

void						CMediaStreamSinkDialogData::selectCodec( int index )
{
	assert( index >= 0 && index < (int) m_pCodecList->size() );
	m_selectedCodec = index;
}

void			CMediaStreamSinkDialogData::selectUncompressed( int index )
{
	assert( index >= 0 && index < s_UncompressedFormatListCount );
	m_selectedUCFormat = index;
}

bool			CMediaStreamSinkDialogData::selectedCodecHasDialog()
{
	return getSelectedCodec()->hasDialog();
}

void			CMediaStreamSinkDialogData::callCodecDialog( HWND hParent )
{
	getSelectedCodec()->callDialog( hParent );
}


std::wstring	CMediaStreamSinkDialogData::getPreferredFilenameExtension()
{
	return getSelectedContainer()->getPreferredFileExtensionW();
}

void			CMediaStreamSinkDialogData::setFilename( const std::wstring& name )
{
	m_FileName = name;
}

std::wstring		CMediaStreamSinkDialogData::getFilename()
{
	return m_FileName;
}

bool			CMediaStreamSinkDialogData::isCustomCodecSupported()
{
	return getSelectedContainer()->isCustomCodecSupported();
}
