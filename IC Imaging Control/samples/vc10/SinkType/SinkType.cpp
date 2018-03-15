///////////////////////////////////////////////////////////////////////////////
//
// This example demonstrates how to write an image stream to an AVI file
// using a AviSink.
//
#define _WIN32_WINNT 0x0500

#include <iostream>
#include <conio.h>
#include <tisudshl.h>

#include "../common/CmdHelper.h"

using namespace _DSHOWLIB_NAMESPACE;

int main(int argc, char* argv[])
{
	DShowLib::InitLibrary();


	Grabber grabber;
	if( !setupDeviceFromFile( grabber ) )
	{
		return -1;
	}

	tCodecListPtr pCodecs = Codec::getAvailableCodecs();

	// Display all codec names on the screen.
	int choice = presentUserChoice( toStringArrayPtrListPtr( pCodecs ) );
	if( choice == -1 )
	{
		return -1;
	}

	std::cout << "Filename : ";	
	std::cin.ignore();
	std::string filename;
	std::getline( std::cin, filename );
	if( filename.empty() )
	{
		return -1;
	}

	// Create an MediaStreamSink to record an AVI file with the selected CoDec
	tMediaStreamSinkPtr pSink = MediaStreamSink::create( 
		MediaStreamContainer::create( MSC_AviContainer ), pCodecs->at( choice ) );

	// Set the filename.
	pSink->setFilename( filename );

	// The sink is initially paused, so that no video data is written to the file.
	pSink->setSinkMode( GrabberSinkType::ePAUSE );

	// Set pSink as the current sink.
	grabber.setSinkType( pSink );

	// Start the live mode. The live video will be displayed but no images will be written
	// to the AVI file because pSink is in pause mode.
	if( !grabber.startLive( true ) )
	{
		std::cerr << grabber.getLastError().toString() << std::endl;
		return -1;
	}

	std::cout << "Press [enter] to start capturing!";
	std::cin.get();

	// Start the sink. The image stream is written to the AVI file.
	pSink->setSinkMode(GrabberSinkType::eRUN );

	std::cout << "Video recording started." << std::endl;
	std::cout << "Press [enter] to stop capturing!";
	std::cin.get();

	// Pause the sink. This stops writing the image stream to the AVI file.
	// A subsequent call to setSinkMode with GrabberSinkType::eRUN as the
	// parameter would restart AVI recording.
	pSink->setSinkMode(GrabberSinkType::ePAUSE );

	std::cout << "Video recording stopped." << std::endl;

	// Stop the live mode. This stops writing images to the AVI file if the mode is not
	// GrabberSinkType::ePAUSE. The AVI file is closed.
	grabber.stopLive();

	std::cout << "Press [enter] to continue." << std::endl;
	std::cin.get();
	return 0;
}
