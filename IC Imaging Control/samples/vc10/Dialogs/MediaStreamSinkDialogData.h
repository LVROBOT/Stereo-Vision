
#ifndef _MEDIASTREAMSINKDIALOGDATA_H_INC_
#define _MEDIASTREAMSINKDIALOGDATA_H_INC_

#include <string>

#include <tisudshl.h>

enum	tContentType 
{
	eCodec = 0,
	eUncompressed,
	eUnspecified
};

class CMediaStreamSinkDialogData
{
public:
	CMediaStreamSinkDialogData( smart_ptr<_DSHOWLIB_NAMESPACE::GrabberSinkType> pOldSink = 0 );

	void createClone( smart_ptr<_DSHOWLIB_NAMESPACE::MediaStreamSink> pOldSink );
	void createDefault();

	smart_ptr<_DSHOWLIB_NAMESPACE::MediaStreamSink>	createSink();

public:
	std::vector<std::wstring>	getContainerList();
	std::vector<std::wstring>	getCompressorList();
	std::vector<std::wstring>	getUncompressedList();

	int							getSelectedContainerIndex();
	int							getSelectedCodecIndex();
	int							getSelectedUncompressedIndex();
	tContentType				getSelectedContainerType();
	
	void						selectContainerType( tContentType type );
	void						selectContainer( int index );
	void						selectCodec( int index );
	void						selectUncompressed( int index );

	bool						selectedCodecHasDialog();
	void						callCodecDialog( HWND hParent = 0 );

	std::wstring				getPreferredFilenameExtension();
	void						setFilename( const std::wstring& name );
	std::wstring				getFilename();

	bool						isCustomCodecSupported();

	_DSHOWLIB_NAMESPACE::tCodecPtr					getSelectedCodec();
	_DSHOWLIB_NAMESPACE::tMediaStreamContainerPtr	getSelectedContainer();
	GUID											getSelectedUCFormat();
	std::wstring									getSelectedUCFormatName();

private:

	void						init( smart_ptr<_DSHOWLIB_NAMESPACE::MediaStreamSink> pOldSink );

	_DSHOWLIB_NAMESPACE::tMediaStreamContainerListPtr m_pContainerList;
	_DSHOWLIB_NAMESPACE::tCodecListPtr				m_pCodecList;

private:
	_DSHOWLIB_NAMESPACE::tFrameFilterList	m_filterList;
	int				m_selectedContainer;
	int				m_selectedCodec;
	int				m_selectedUCFormat;
	std::wstring	m_FileName;

	tContentType	m_type;
};

#endif
