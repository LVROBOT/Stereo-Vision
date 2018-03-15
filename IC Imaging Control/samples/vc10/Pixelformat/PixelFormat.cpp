///////////////////////////////////////////////////////////////////////////////
//
// This example demonstrates how to directly manipulate the pixels in the image buffer.
// It also gives an overview over the common color formats and how the pixels of each format 
// are organized in the buffer.
//
#define _WIN32_WINNT 0x0500

#include <conio.h>
#include <tisudshl.h>

#include "../Common/CmdHelper.h"

using namespace _DSHOWLIB_NAMESPACE;

MemBufferCollection::tMemBufferPtr	getSingleFrame( Grabber& gr, tColorformatEnum type )
{
	smart_ptr<FrameHandlerSink> pHandlerSink = FrameHandlerSink::create( type, 1 );
	pHandlerSink->setSnapMode( true );

	gr.setSinkType( pHandlerSink );

	gr.startLive( false );
	Sleep( 250 ); // give the device time to adjust automatic settings i.e. auto exposure
	pHandlerSink->snapImages( 1, 2000 );
	gr.stopLive();

	// get pointer to the image data
	return pHandlerSink->getLastAcqMemBuffer();
}

unsigned __int16 byteSwap( unsigned __int16 x )
{
	BYTE* p = (BYTE*)&x;
	return ((unsigned int)p[0] << 8) | p[1];
}

unsigned __int16 YGB0PixelFromInt16Value( unsigned __int16 value )
{
	return byteSwap( value << 6 );
}

unsigned __int16 Int16ValueFromYGB0Pixel( unsigned __int16 pixel )
{
	return byteSwap( pixel ) >> 6;
}

unsigned __int16 YGB1PixelFromInt16Value( unsigned __int16 value )
{
	return byteSwap( value );
}

unsigned __int16 Int16ValueFromYGB1Pixel( unsigned __int16 pixel )
{
	return byteSwap( pixel );
}


int main(int argc, char* argv[])
{
	// Initialize the library.
	DShowLib::InitLibrary();


	Grabber grabber;

	// Disable overlay. If it was in the graph, we could not get UYVY or 16-bit images.
	grabber.setOverlayBitmapPathPosition( ePP_NONE );

	if( !setupDeviceFromFile( grabber ) )
	{
		return -1;
	}

	{
		// *************************************************************************
		// image buffer pixel format is set to eRGB8

		MemBufferCollection::tMemBufferPtr pActiveBuf = getSingleFrame( grabber, eRGB8 );

		// get pointer to the image data
		BYTE* pbImgData = pActiveBuf->getPtr();
		
		// Calculate the index of the upper left pixel
		// Images are stored upside down in the image buffer
		SIZE dim = pActiveBuf->getFrameType().dim;
		int iOffsUpperLeft = (dim.cy-1) * dim.cx;

		printf( "\nImage buffer pixel format is eRGB8\n" );
		printf( "Pixel 1: %d\n", pbImgData[iOffsUpperLeft  ] );
		printf( "Pixel 2: %d\n", pbImgData[iOffsUpperLeft+1] );

		// overwrite the first 3 pixels and save image to disk
		pbImgData[iOffsUpperLeft  ] = 0;	// Set the first pixel to BLACK
		pbImgData[iOffsUpperLeft+1] = 128;	// Set the second pixel to GRAY
		pbImgData[iOffsUpperLeft+2] = 255;	// Set the third pixel to WHITE
		
		pActiveBuf->save( "RGB8.bmp" );
		printf( "Image saved to file \"RGB8.bmp\"\n" );
	}

	{
		// *************************************************************************
		// image buffer pixel format is set to eY800

		MemBufferCollection::tMemBufferPtr pActiveBuf = getSingleFrame( grabber, eY800 );

		// get pointer to the image data
		BYTE* pbImgData = pActiveBuf->getPtr();

		// Calculate the index of the upper left pixel
		// Images are stored top-down in the image buffer, so the first pixel has index 0.
		int iOffsUpperLeft = 0;

		printf( "\nImage buffer pixel format is eY800\n" );
		printf( "Pixel 1: %d\n", pbImgData[iOffsUpperLeft  ] );
		printf( "Pixel 2: %d\n", pbImgData[iOffsUpperLeft+1] );

		// overwrite the first 3 pixels and save image to disk
		pbImgData[iOffsUpperLeft  ] = 0;	// Set the first pixel to BLACK
		pbImgData[iOffsUpperLeft+1] = 128;	// Set the second pixel to GRAY
		pbImgData[iOffsUpperLeft+2] = 255;	// Set the third pixel to WHITE

		pActiveBuf->save( "Y800.bmp" );
		printf( "Image saved to file \"Y800.bmp\"\n" );
	}

	{
		// *************************************************************************
		// image buffer pixel format is set to eRGB24

		MemBufferCollection::tMemBufferPtr pActiveBuf = getSingleFrame( grabber, eRGB24 );

		struct RGB24Pixel {
			BYTE b;
			BYTE g;
			BYTE r;
		};
		RGB24Pixel* pbImgData = (RGB24Pixel*) pActiveBuf->getPtr();

		// Calculate the index of the upper left pixel
		// Images are stored upside down in the image buffer
		SIZE dim = pActiveBuf->getFrameType().dim;
		int iOffsUpperLeft = (dim.cy-1) * dim.cx;

		printf( "\nImage buffer pixel format is eRGB24\n" );
		// Please note: RGB values are stored in the following order: B,G,R
		printf( "Pixel 1(RGB): %d %d %d\n", pbImgData[iOffsUpperLeft].r,	//RED
											pbImgData[iOffsUpperLeft].g,	//GREEN
											pbImgData[iOffsUpperLeft].b );	//BLUE
		printf( "Pixel 2(RGB): %d %d %d\n", pbImgData[iOffsUpperLeft+1].r,	//RED
											pbImgData[iOffsUpperLeft+1].g,	//GREEN
											pbImgData[iOffsUpperLeft+1].b );	//BLUE

		// overwrite the first 3 pixels and save image to disk
		// Set the first pixel to RED
		pbImgData[iOffsUpperLeft].b = 0;	// BLUE
		pbImgData[iOffsUpperLeft].g = 0;	// GREEN
		pbImgData[iOffsUpperLeft].r = 255;	// RED

		// Set the second pixel to GREEN
		pbImgData[iOffsUpperLeft+1].b = 0;	// BLUE
		pbImgData[iOffsUpperLeft+1].g= 255;	// GREEN
		pbImgData[iOffsUpperLeft+1].r = 0;	// RED

		// Set the third pixel to BLUE
		pbImgData[iOffsUpperLeft+2].b = 255;	// BLUE
		pbImgData[iOffsUpperLeft+2].g = 0;	// GREEN
		pbImgData[iOffsUpperLeft+2].r = 0;	// RED

		saveToFileBMP( *pActiveBuf, "RGB24.bmp" );
		printf( "Image saved to file \"RGB24.bmp\"\n" );
	}

	{
		// *************************************************************************
		// image buffer pixel format is set to eRGB32

		MemBufferCollection::tMemBufferPtr pActiveBuf = getSingleFrame( grabber, eRGB32 );

		RGBQUAD* pbImgData = (RGBQUAD*)pActiveBuf->getPtr();

		// Calculate the index of the upper left pixel
		// Images are stored upside down in the image buffer
		SIZE dim = pActiveBuf->getFrameType().dim;
		int iOffsUpperLeft = (dim.cy-1) * dim.cx;

		printf( "\nImage buffer pixel format is eRGB32\n" );
		printf( "Pixel 1(RGBA): %d %d %d %d\n", pbImgData[iOffsUpperLeft].rgbRed,
							  					pbImgData[iOffsUpperLeft].rgbGreen,
												pbImgData[iOffsUpperLeft].rgbBlue,
												pbImgData[iOffsUpperLeft].rgbReserved );
		printf( "Pixel 2(RGBA): %d %d %d %d\n", pbImgData[iOffsUpperLeft+1].rgbRed,
							  					pbImgData[iOffsUpperLeft+1].rgbGreen,
												pbImgData[iOffsUpperLeft+1].rgbBlue,
												pbImgData[iOffsUpperLeft+1].rgbReserved );

		// overwrite first 3 pixels and save image to disk
		// Set the first pixel to RED
		pbImgData[iOffsUpperLeft].rgbRed = 0xff;	
		pbImgData[iOffsUpperLeft].rgbGreen = 0;		
		pbImgData[iOffsUpperLeft].rgbBlue = 0;		
		pbImgData[iOffsUpperLeft].rgbReserved = 0;	

		// Set the second pixel to GREEN
		pbImgData[iOffsUpperLeft+1].rgbRed = 0;	
		pbImgData[iOffsUpperLeft+1].rgbGreen = 0xff;
		pbImgData[iOffsUpperLeft+1].rgbBlue = 0;
		pbImgData[iOffsUpperLeft+1].rgbReserved = 0;

		// Set the third pixel to BLUE
		pbImgData[iOffsUpperLeft+2].rgbRed = 0;	
		pbImgData[iOffsUpperLeft+2].rgbGreen = 0;
		pbImgData[iOffsUpperLeft+2].rgbBlue = 0xff;
		pbImgData[iOffsUpperLeft+2].rgbReserved = 0;

		saveToFileBMP( *pActiveBuf, "RGB32.bmp" );
		printf( "Image saved to file \"RGB32.bmp\"\n" );
	}
	/*********************************************************************************/

	{
		// *************************************************************************
		// image buffer pixel format is set to eRGB555

		MemBufferCollection::tMemBufferPtr pActiveBuf = getSingleFrame( grabber, eRGB555 );

		WORD* pwImgData = (WORD*) pActiveBuf->getPtr();		

		// Calculate the index of the upper left pixel
		// Images are stored upside down in the image buffer
		// * 1: a pixel is 2 byte, but since we have a WORD pointer (which is also 2 bytes)
		// we count in pixel not in bytes
		SIZE dim = pActiveBuf->getFrameType().dim;
		int iOffsUpperLeft = (dim.cy-1) * dim.cx * 1;

		// Please note: RGB values are stored within a WORD in the following order: R,G,B
		// A binary AND operation is done with the color mask to extract the specific color.
		// After the AND operation, a right shift is done so that the output is displayed correctly.
		printf( "\nImage buffer pixel format is eRGB555\n" );

		printf( "Pixel 1(RGB): %d %d %d\n", ( pwImgData[iOffsUpperLeft] & eRGB555_R ) >> 10 ,
			( pwImgData[iOffsUpperLeft] & eRGB555_G ) >> 5,
			( pwImgData[iOffsUpperLeft] & eRGB555_B ) );
		printf( "Pixel 2(RGB): %d %d %d\n", ( pwImgData[iOffsUpperLeft+1] & eRGB555_R ) >> 10 ,
			( pwImgData[iOffsUpperLeft+1] & eRGB555_G ) >> 5,
			( pwImgData[iOffsUpperLeft+1] & eRGB555_B ) );


		// overwrite the first 3 pixels and save image to disk
		// set the first pixel to RED
		pwImgData[iOffsUpperLeft] = 0;			// clear the pixel
		pwImgData[iOffsUpperLeft] |= 31 << 10;	// Assign the value for red

		// set the second pixel to GREEN
		pwImgData[iOffsUpperLeft+1] = 0;		// clear the pixel
		pwImgData[iOffsUpperLeft+1] |= 31 << 5;	// Assign the value for green

		// set the third pixel to BLUE
		pwImgData[iOffsUpperLeft+2] = 0;		// clear the pixel
		pwImgData[iOffsUpperLeft+2] |= 31;		// Assign the value for blue

		pActiveBuf->save( "RGB555.bmp" );
		printf( "Image saved to file \"RGB555.bmp\"\n" );
	}


	{
		// *************************************************************************
		// image buffer pixel format is set to eRGB565

		MemBufferCollection::tMemBufferPtr pActiveBuf = getSingleFrame( grabber, eRGB565 );

		WORD* pwImgData = (WORD*) pActiveBuf->getPtr();		

		// Calculate the index of the upper left pixel
		// Images are stored upside down in the image buffer
		// * 1: a pixel is 2 byte, but since we have a WORD pointer (which is also 2 bytes)
		// we count in pixel not in bytes
		SIZE dim = pActiveBuf->getFrameType().dim;
		int iOffsUpperLeft = (dim.cy-1) * dim.cx * 1;

		// Please note: RGB values are stored within a WORD in the following order: R,G,B
		// A binary AND operation is done with the color mask to extract the specific color.
		// After the AND operation, a right shift is done so that the output is displayed correctly.
		printf( "\nImage buffer pixel format is eRGB565\n" );
		printf( "Pixel 1(RGB): %d %d %d\n", ( pwImgData[iOffsUpperLeft] & eRGB565_R ) >> 11,
			( pwImgData[iOffsUpperLeft] & eRGB565_G ) >> 5,
			( pwImgData[iOffsUpperLeft] & eRGB565_B ) );
		printf( "Pixel 2(RGB): %d %d %d\n", ( pwImgData[iOffsUpperLeft+1] & eRGB565_R ) >> 11 ,
			( pwImgData[iOffsUpperLeft+1] & eRGB565_G ) >> 5,
			( pwImgData[iOffsUpperLeft+1] & eRGB565_B ) );

		// overwrite the first 3 pixels and save image to disk
		// set the first pixel to RED
		pwImgData[iOffsUpperLeft] = 0;			// clear the pixel
		pwImgData[iOffsUpperLeft] |= 31 << 11;	// Assign the value for red

		// set the second pixel to GREEN
		pwImgData[iOffsUpperLeft+1] = 0;		// clear the pixel
		pwImgData[iOffsUpperLeft+1] |= 63 << 5;	// Assign the value for green

		// set the third pixel to BLUE
		pwImgData[iOffsUpperLeft+2] = 0;		// clear the pixel
		pwImgData[iOffsUpperLeft+2] |= 31;		// Assign the value for blue

		pActiveBuf->save( "RGB565.bmp" );
		printf( "Image saved to file \"RGB565.bmp\"\n" );

	}
	/*********************************************************************************/

	// If the source video format is UYVY, we can grab it.
	if( getColorformatFromSubtype( grabber.getVideoFormat().getColorformat() ) == eUYVY )
	{
		// *************************************************************************
		// image buffer pixel format is set to eUYVY

		MemBufferCollection::tMemBufferPtr pActiveBuf = getSingleFrame( grabber, eUYVY );

		// UYVY Images are stored top-down, so the upper left pixel starts at byte 0.
		// Each 4 bytes represent the color for 2 neighboring pixels:
		// 
		// [ U0 | Y0 | V0 | Y1 ]
		//
		// Y0 is the brightness of pixel 0, Y1 the brightness of pixel 1.
		// U0 and V0 is the color of both pixels.
		struct UYVYQuad
		{
			BYTE U0;
			BYTE Y0;
			BYTE V0;
			BYTE Y1;
		};
		UYVYQuad* pImgData = (UYVYQuad*)pActiveBuf->getPtr();

		// Calculate the index of the upper left pixel
		// Images are stored top-down in the image buffer, so the first two pixels have index 0.
		int iOffsUpperLeft = 0;

		printf( "\nImage buffer pixel format is eUYVY\n" );
		printf( "Pixel 1 (Y U V): %d %d %d\n", pImgData[iOffsUpperLeft].Y0,
			pImgData[iOffsUpperLeft].U0, pImgData[iOffsUpperLeft].V0 );
		printf( "Pixel 2 (Y U V): %d %d %d\n", pImgData[iOffsUpperLeft].Y1,
			pImgData[iOffsUpperLeft].U0, pImgData[iOffsUpperLeft].V0 );
		printf( "Pixel 3 (Y U V): %d %d %d\n", pImgData[iOffsUpperLeft+1].Y0,
			pImgData[iOffsUpperLeft+1].U0, pImgData[iOffsUpperLeft+1].V0 );
		printf( "Pixel 4 (Y U V): %d %d %d\n", pImgData[iOffsUpperLeft+1].Y1,
			pImgData[iOffsUpperLeft+1].U0, pImgData[iOffsUpperLeft+1].V0 );

		// Overwrite the first 6 pixels and save image to disk
		// set the first 2 pixels to RED
		pImgData[0].U0 = 90;
		pImgData[0].V0 = 240;
		pImgData[0].Y0 = 82;
		pImgData[0].Y1 = 164;	// Make the 2nd pixel brighter

		// set the 3rd and 4th to GREEN
		pImgData[1].U0 = 54;
		pImgData[1].V0 = 34;
		pImgData[1].Y0 = 145;
		pImgData[1].Y1 = 72;	// Make the 2nd pixel darker

		// set the 5th and 6th pixel to BLUE
		pImgData[2].U0 = 240;
		pImgData[2].V0 = 110;
		pImgData[2].Y0 = 41;
		pImgData[2].Y1 = 82;	// Make the 2nd pixel brighter

		// The values above were calculated using the following formulas:
		//
		//	Y  =  (0.257 * R) + (0.504 * G) + (0.098 * B) + 16
		//  V  =  (0.439 * R) - (0.368 * G) - (0.071 * B) + 128
		//  U  = -(0.148 * R) - (0.291 * G) + (0.439 * B) + 128
		//

		// We save the buffer as RGB24, so that other software can view it.
		saveToFileBMP( *pActiveBuf, "UYVY.bmp", eRGB24 );
		printf( "Image saved to file \"UYVY.bmp\"\n" );
	}
	else
	{
		printf( "\nTo show the UYVY pixel format, select a UYVY video format\n" );
	}
	/*********************************************************************************/

	// If the source video format is YGB0 (so a 16 bit gray format), we can grab it.
	if( grabber.getVideoFormat().getSubtype() == _DSHOWLIB_NAMESPACE::MEDIASUBTYPE_YGB0 )
	{
		// *************************************************************************
		// image buffer pixel format is set to YGB0

		MemBufferCollection::tMemBufferPtr pActiveBuf = getSingleFrame( grabber, eYGB0 );

		// YGB0 Images are stored top-down, so the upper left pixel starts at byte 0.
		// 2 Byte represent one pixel.
		unsigned __int16* pImgData = (unsigned __int16*)pActiveBuf->getPtr();

		// To get a "value" (in range 0-1023) for the pixel, use
		// Int16ValueFromYGB0Pixel:
		unsigned __int16 val0 = Int16ValueFromYGB0Pixel( pImgData[0] );
		unsigned __int16 val1 = Int16ValueFromYGB0Pixel( pImgData[1] );

		printf( "\nImage buffer pixel format is eYGB0\n" );
		printf( "Pixel 1 (Y16): %d\n", val0 );
		printf( "Pixel 2 (Y16): %d\n", val1 );

		pImgData[0] = YGB0PixelFromInt16Value( 0 );		// Set the first pixel to BLACK
		pImgData[1] = YGB0PixelFromInt16Value( 511 );	// Set the second pixel to GRAY
		pImgData[2] = YGB0PixelFromInt16Value( 1023 );	// Set the third pixel to WHITE

		// We save the buffer as RGB24, so that other software can view it.
		saveToFileBMP( *pActiveBuf, "YGB0.bmp", eRGB24 );
		printf( "Image saved to file \"YGB0.bmp\"\n" );
	}
	else
	{
		printf( "\nTo show the YGB0 pixel format, select a YGB0 video format\n" );
	}
	/*********************************************************************************/

	// If the source video format is YGB1 (so a 16 bit gray format), we can grab it.
	if( grabber.getVideoFormat().getSubtype() == _DSHOWLIB_NAMESPACE::MEDIASUBTYPE_YGB1 )
	{
		// *************************************************************************
		// image buffer pixel format is set to YGB1

		MemBufferCollection::tMemBufferPtr pActiveBuf = getSingleFrame( grabber, eYGB1 );

		// YGB1 Images are stored top-down, so the upper left pixel starts at byte 0.
		// 2 Byte represent one pixel.
		unsigned __int16* pImgData = (unsigned __int16*)pActiveBuf->getPtr();

		// To get a "value" (in range 0-1023) for the pixel, use
		// Int16ValueFromYGB1Pixel:
		unsigned __int16 val0 = Int16ValueFromYGB1Pixel( pImgData[0] );
		unsigned __int16 val1 = Int16ValueFromYGB1Pixel( pImgData[1] );

		printf( "\nImage buffer pixel format is eYGB1\n" );
		printf( "Pixel 1 (Y16): %d\n", val0 );
		printf( "Pixel 2 (Y16): %d\n", val1 );

		pImgData[0] = YGB1PixelFromInt16Value( 0 );		// Set the first pixel to BLACK
		pImgData[1] = YGB1PixelFromInt16Value( 511 );	// Set the second pixel to GRAY
		pImgData[2] = YGB1PixelFromInt16Value( 1023 );	// Set the third pixel to WHITE

		// We save the buffer as RGB24, so that other software can view it.
		saveToFileBMP( *pActiveBuf, "YGB1.bmp", eRGB24 );
		printf( "Image saved to file \"YGB1.bmp\"\n" );
	}
	else
	{
		printf( "\nTo show the YGB1 pixel format, select a YGB1 video format\n" );
	}
	/*********************************************************************************/

	// If the source video format is Y16 (so a 16 bit gray format), we can grab it.
	if( grabber.getVideoFormat().getSubtype() == _DSHOWLIB_NAMESPACE::MEDIASUBTYPE_Y16 )
	{
		// *************************************************************************
		// image buffer pixel format is set to Y16

		MemBufferCollection::tMemBufferPtr pActiveBuf = getSingleFrame( grabber, eY16 );

				// Y16 Images are stored top-down, so the upper left pixel starts at byte 0.
		// 2 Byte represent one pixel.
		unsigned __int16* pImgData = (unsigned __int16*)pActiveBuf->getPtr();
		
				// The Y16 pixel values exactly map unsigned 16-bit integers:
		unsigned __int16 val0 = pImgData[0];
		unsigned __int16 val1 = pImgData[1];

		printf( "\nImage buffer pixel format is eY16\n" );
		printf( "Pixel 1 (Y16): %d\n", val0 );
		printf( "Pixel 2 (Y16): %d\n", val1 );
		
				pImgData[0] = 0;		// Set the first pixel to BLACK
		pImgData[1] = 32768;	// Set the second pixel to GRAY
		pImgData[2] = 65535;	// Set the third pixel to WHITE

		// We save the buffer as TIFF, so that other software can view it.
		saveToFileTIFF( *pActiveBuf, "Y16.tiff" );
				printf( "Image saved to file \"Y16.tiff\"\n" );
	}
	else
	{
		printf( "\nTo show the Y16 pixel format, select a Y16 video format\n" );
	}
	/*********************************************************************************/

	printf("Press any key to continue.");
	getch();

	return 0;
}
