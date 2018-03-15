///////////////////////////////////////////////////////////////////////////////
//
// This example demonstrates how to use a GrabberListener derived
// callback handler object to process events
//
// A class CListener is derived from GrabberListener. It is used to handle callbacks.
// The method CListener::frameReady() simulates a time expensive processing. Therefore,
// the method CListener::frameReady() is not called for every captured buffer. 
// The member CListener::m_pBufferWritten is used to record, which buffers were processed
// by CListener::frameReady().
// After snapImages() returns, the main function will save the buffers that were not
// processed. This sample shows that all buffers have been copied correctly to the
// MembufferCollection, although CListener::frameReady() was not called for every buffer.
//

#define _WIN32_WINNT 0x0500

#include <iostream>
#include <conio.h>

#include <tisudshl.h>

#include "CmdHelper.h"
#include "Listener.h"

using namespace _DSHOWLIB_NAMESPACE;

// Specify the number of buffers to be used.
#define NUM_BUFFERS 10

int main(int argc, char* argv[])
{

	DShowLib::InitLibrary();

	atexit( ExitLibrary );

	Grabber grabber;

	// Create the GrabberListener object.
	// CListener is derived from GrabberListener.
	CListener *pListener = new CListener();
												
	if( !setupDeviceFromFile( grabber ) )
	{
		return -1;
	}
	
	// Assign the number of buffers to the cListener object.
	pListener->setBufferSize( NUM_BUFFERS );

	// Enable the overlay bitmap to display the frame counter in the live video.
	grabber.getOverlay()->setEnable( true );

	// Register the pListener object for the frame ready and 
	// the overlay callback event.
	grabber.addListener( pListener, GrabberListener::eFRAMEREADY|
										GrabberListener::eOVERLAYCALLBACK );


	// Create a FrameTypeInfoArray data structure describing the allowed color formats.
	FrameTypeInfoArray acceptedTypes = FrameTypeInfoArray::createRGBArray();

	// Create the frame handler sink
	smart_ptr<FrameHandlerSink> pSink = FrameHandlerSink::create( acceptedTypes, NUM_BUFFERS );

	// enable snap mode (formerly tFrameGrabberMode::eSNAP).
	pSink->setSnapMode( true );

	// Apply the sink to the grabber.
	grabber.setSinkType( pSink );

	grabber.startLive();				// Start the grabber.

	pSink->snapImages( NUM_BUFFERS );	// Grab NUM_BUFFERS images.

	grabber.stopLive();					// Stop the grabber.
	
	// Save the buffers for which CListener::frameReady() has not been called.
	// Since CListener::frameReady() calls Sleep(250), it cannot be called for
	// every buffer. Nevertheless, all buffers are copied to the MemBufferCollection.
	for( size_t i = 0; i < pListener->m_BufferWritten.size(); i++ )
	{
		if( !pListener->m_BufferWritten[i] )
		{
			std::cout << "Buffer " << i << " processed in main()." << std::endl;
			pListener->saveImage( pSink->getMemBufferCollection()->getBuffer( i ), i);
		}
	}
	// The CListener object must be unregistered for all events
	// before it may be destroyed.
	grabber.removeListener( pListener );

	// Now, it must be checked whether the CListener object has been unregistered
	// for all events.
	while( grabber.isListenerRegistered( pListener ) )
	{
		Sleep( 0 ); // Wait and give pending callbacks a chance to complete.
	}

	// Now, the application can be sure that no callback methods of pListener
	// will be called anymore. It is now safe to delete pListener.
	delete pListener;

	std::cout << "Press any key to continue!" << std::endl;
	std::cin.get();
	return 0;
}

