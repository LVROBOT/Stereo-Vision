///////////////////////////////////////////////////////////////////////////////
// This example demonstrates how to setup a MemBuffer collection and use it to
// capture images. The captured images will be saved to BMP files. 	
//
#define _WIN32_WINNT 0x0500
#include <iostream>

#include <tisudshl.h>
#include "../Common/CmdHelper.h"

using namespace _DSHOWLIB_NAMESPACE;

int		main(int argc, char* argv[])
{
	// Initialize the library.
	DShowLib::InitLibrary();



	Grabber grabber;
	if( !setupDeviceFromFile( grabber ) )
	{
		return -1;
	}

	grabber.setOverlayBitmapPathPosition( ePP_NONE );

	// Set the image buffer format to eY800. eY800 means monochrome, 8 bits (1 byte) per pixel.
	// Let the sink create a matching MemBufferCollection with 1 buffer.
	tFrameHandlerSinkPtr pSink = FrameHandlerSink::create( eY800, 1 );

	// We use snap mode.
	pSink->setSnapMode( true );

	// Set the sink.
	grabber.setSinkType( pSink );	

	// Prepare the live mode, to get the output size if the sink.
	if( !grabber.prepareLive( false ) )
	{
		std::cerr << "Could not render the VideoFormat into a eY800 sink.";
		return -1;
	}

	// Retrieve the output type and dimension of the handler sink.
	// The dimension of the sink could be different from the VideoFormat, when
	// you use filters.
	FrameTypeInfo info;
	pSink->getOutputFrameType( info );

	BYTE* pBuf[5];
	// Allocate 5 image buffers of the above calculate buffer size.
	for( int i = 0; i < 5; ++i )
	{
		pBuf[i] = new BYTE[info.buffersize];
	}

	// Create a new MemBuffer collection that uses our own image buffers.
	tMemBufferCollectionPtr pCollection = MemBufferCollection::create( info, 5, pBuf );
	if( pCollection == 0 || !pSink->setMemBufferCollection( pCollection ) )
	{
		std::cerr << "Could not set the new MemBufferCollection, because types do not match.";
		return -1;
	}

	// Start live mode for fast snapping. The live video will not be displayed,
	// because false is passed to startLive().
	grabber.startLive( false );
	
	// Snap 5 images. The images are copied to the MemBufferCollection the
	// application created above.
	pSink->snapImages( 5 );
	
	// Stop the live video.
	grabber.stopLive();
	
	// Close the device.
	grabber.closeDev();

	// Save the five captured images in the MemBuffer collection to separate files.
	pCollection->save( "file*.bmp" );

	// Free the five buffers in the MemBuffer collection.
	for( int j = 0; j < 5; ++j )
	{
		delete pBuf[j];
	}

	return 0;
}

