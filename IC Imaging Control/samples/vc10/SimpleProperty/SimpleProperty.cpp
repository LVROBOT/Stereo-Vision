// SimpleProperty.cpp : Defines the entry point for the console application.
//

#define _WIN32_WINNT 0x0500

#include <iostream>
#include <tchar.h>

#include <tisudshl.h>

#include "../Common/SimplePropertyAccess.h"

using namespace DShowLib;

int main( int argc, char* argv[] )
{
		DShowLib::InitLibrary();

	atexit( ExitLibrary );

	Grabber grabber;
	grabber.showDevicePage();

	if( !grabber.isDevValid() )
	{
		std::cerr << "No valid device selected" << std::endl;
	}
	else
	{
		CSimplePropertyAccess prop( grabber.getAvailableVCDProperties() );

		if( prop.isAvailable( VCDID_Brightness ) )
		{
			std::cout << "Brightness property available" << std::endl;

			if( prop.getAuto( VCDID_Brightness ) )
			{
				std::cout << "Brightness auto enabled" << std::endl;
			}
			else
			{
				std::cout << "Brightness auto disabled" << std::endl;

				long val = prop.getValue( VCDID_Brightness );
				std::cout << "Current Brightness value: " << val << std::endl;
				
				long min = prop.getRangeMin( VCDID_Brightness );
				long max = prop.getRangeMax( VCDID_Brightness );
				std::cout << "Brightness Range: [" << min << ".." << max << "]" << std::endl;
			}
		}
		else
		{
			std::cout << "Brightness property not available" << std::endl;
		}
	}

	std::cin.get();

	return 0;
}

