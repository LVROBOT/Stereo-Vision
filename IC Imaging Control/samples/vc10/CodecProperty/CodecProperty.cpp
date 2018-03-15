///////////////////////////////////////////////////////////////////////////////
//
// This example demonstrates how to set an avi sink type and to set the parameter
// for a video codec (compressor). It shows, how to retrieve the data in a memory
// block and save it into a binary file.
//
#define _WIN32_WINNT 0x0500

#include <tisudshl.h>
#include <windows.h>
#include <conio.h>
#include <fstream>

#include "../Common/CmdHelper.h"

using namespace _DSHOWLIB_NAMESPACE;

//////////////////////////////////////////////////////////////////////////
/*! Save the configuration data of the specified codec to a file. */
bool	writeCodecConfigFile( Codec& codec, const std::string& filename )
{
	bool bSucceded = false;
	std::string codec_settings = codec.getSettings();
	if( !codec_settings.empty() )
	{
		std::ofstream file( filename.c_str() );
		if( file.good() )
		{
			file << codec_settings;
			bSucceded = true;
		}
		else
		{
			std::cerr << "Error : Could not open file " << filename << std::endl;
		}
	}
	else
	{
		std::cerr << "Error : No data available from the codec" << std::endl;
	}
	return bSucceded;
}

//////////////////////////////////////////////////////////////////////////
/*! Read the codec configuration data for the specified codec from
    the specified file and assign the data to the codec.
*/
bool	readCodecConfigFile( Codec& codec, const std::string& filename )
{
	bool bSucceded = false;

	std::ifstream file( filename.c_str() );
	if( file.good() )
	{
		std::string codec_settings;
		while( file.good() )	// read the file char by char
		{
			codec_settings += file.get();
		}
		if( !codec_settings.empty() )	// no data in the file check
		{
			if( codec.setSettings( codec_settings ) )	// set the data
			{
				bSucceded = true;
			}
			else
			{
				std::cerr << "Error : Data does not fit codec" << std::endl;
			}
		}
		else
		{
			std::cerr << "Error : No data found in the supplied file" << std::endl;
		}
	}
	else
	{
		std::cerr << "Error : Could not open file " << filename << std::endl;
	}
	return bSucceded;
}

int main(int argc, char* argv[])
{
	DShowLib::InitLibrary();

	atexit( ExitLibrary );

	Grabber grabber;

	if( !setupDeviceFromFile( grabber ) )
	{
		return -1;
	}

	// Get a list of all available video compressors (codecs)
	tCodecListPtr pCodecList = Codec::getAvailableCodecs();
	int choice = presentUserChoice( toStringArrayPtrListPtr( pCodecList ) );
	if( choice == -1 )
	{
	 	return -1;
	}

	smart_ptr<Codec> pCodec = pCodecList->at(choice);
	if( pCodec->hasDialog() )
	{
		pCodec->callDialog();
	}
	else
	{
		std::cout << "The selected codec has no configuration dialog!" << std::endl;
	}

	writeCodecConfigFile( *pCodec, "codec.xml" );
	readCodecConfigFile( *pCodec, "codec.xml" );

	std::cout << "Filename : ";	
	std::cin.ignore();
	std::string filename;
	std::getline( std::cin, filename );
	if( filename.empty() )
	{
		return -1;
	}

	smart_ptr<MediaStreamSink> pSink = MediaStreamSink::create( MSC_AviContainer, pCodec );

	// Set the filename.
	pSink->setFilename( filename );

	// Attach the created sink
	grabber.setSinkType( pSink );

	std::cout << "Press [enter] to start capturing!";
	std::cin.get();

	// Start the live mode. The grabbed images will be displayed during
	// grabbing.  This starts writing the avi file to disk.
	if( !grabber.startLive( true ) )
	{
		std::cerr << grabber.getLastError().toString() << std::endl;
		return -1;
	}

	std::cout << "Press [enter] to stop capturing!";
	std::cin.get();

	// Stop the live mode. This stops writing the avi file to disk.
	grabber.stopLive();

	std::cout << "Press [enter] to continue." << std::endl;
	std::cin.get();
	return 0;
}
