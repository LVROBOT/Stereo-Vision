///////////////////////////////////////////////////////////////////////////////
//
// This example demonstrates how to query for the available 
// video norms and formats. 
// If the current video capture device supports video norms, the available
// video formats depend on the current video norm. This example allows the user
// to select a video norm in this case, before it retrieves the video formats.
//
// If the current video capture device does not support video norms, the video 
// formats are retrieved immediately.
//
#define _WIN32_WINNT 0x0500

#include "conio.h"

#include <tisudshl.h>
using namespace _DSHOWLIB_NAMESPACE;

#include "../Common/CmdHelper.h"


int main(int argc, char* argv[])
{
	DShowLib::InitLibrary();


	Grabber grabber;

	Grabber::tVidCapDevListPtr pVidCapDevList = grabber.getAvailableVideoCaptureDevices();
	if( pVidCapDevList == 0 || pVidCapDevList->empty() )
	{
	    return -1; // No device available.
	}

	int choice = presentUserChoice( toStringArrayPtr(pVidCapDevList) );
	// Open the selected video capture device.
	if( choice == -1 )
	{
		return -1;
	}
	grabber.openDev( pVidCapDevList->at( choice ) );
	
	// Check whether video norms are available with the current video capture device.
	if( grabber.isVideoNormAvailableWithCurDev() )
	{
		// Query for all available video norms.
		Grabber::tVidNrmListPtr pVidNrmList = grabber.getAvailableVideoNorms();
		
		if( pVidNrmList == 0 )
		{
			std::cerr << "Error: " << grabber.getLastError().toString() << std::endl;
			return -1;
		}
		while ( true )
		{
			std::cout << "Video Norms available for " << grabber.getDev().toString() << std::endl;

			int choice = presentUserChoice( toStringArrayPtr(pVidNrmList) );
			if( choice != -1 )
			{
				// Set the selected video norm before
				// retrieving the according video formats.
				grabber.setVideoNorm( pVidNrmList->at( choice ) );

				std::cout << "\n\nVideo Formats available for " << pVidNrmList->at( choice ).toString() << std::endl;
			
				// Now retrieve the video formats.
				Grabber::tVidFmtListPtr pVidFmtList = grabber.getAvailableVideoFormats();
				if( pVidFmtList == 0 ) // No video formats available?
				{
					std::cerr << "Error : " << grabber.getLastError().toString() << std::endl;
					break;
				}				

				unsigned int counter = 0;
				// List the available video formats.
				for( Grabber::tVidFmtList::iterator it = pVidFmtList->begin(); 
					  it != pVidFmtList->end(); 
					  ++it )
				{
					std::cout << "\t[" << counter++ << "] " << it->toString() << std::endl;
				}

				std::cout << std::endl << std::endl;
			}
			else
			{
				break;
			}
		}
	}
	else
	{
		// If the current video capture device does not support video norms,
		// the available video formats can be retrieved immediately.
		std::cout << "\n\nVideo Formats available: \n";
			
		Grabber::tVidFmtListPtr pVidFmtList = grabber.getAvailableVideoFormats();
			
		if( pVidFmtList == 0 ) // No video formats available?
		{
			std::cerr << "Error : " << grabber.getLastError().toString() << std::endl;
		}
		else
		{
			unsigned int counter = 0;
			// List the available video formats.
			for( Grabber::tVidFmtList::iterator it = pVidFmtList->begin(); 
				it != pVidFmtList->end(); 
				++it )
			{
				std::cout << "\t[" << counter++ << "] " << it->toString() << std::endl;
			}
		}
	}
		
	printf("Press any key to continue");
	getch();
	return 0;
}
//>>