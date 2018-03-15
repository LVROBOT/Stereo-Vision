#define _WIN32_WINNT 0x0500

#include <windows.h>
#include <conio.h>
#include <iostream>
#include <tisudshl.h>

#include "../Common/CmdHelper.h"

using namespace _DSHOWLIB_NAMESPACE;
inline bool	openDeviceFromFile(_DSHOWLIB_NAMESPACE::Grabber& gr, const std::string& devStateFilename)
{
	if (gr.loadDeviceStateFromFile(devStateFilename))
	{
		std::cout << "Device opened from: <" << devStateFilename << ">." << std::endl;
	}
	else
	{
		std::cout << "File <" << devStateFilename << "> either not found, or device could not be opened from it." << std::endl;
	}
	if (!gr.showDevicePage() || !gr.isDevValid())
	{
		return false;
	}
	gr.saveDeviceStateToFile(devStateFilename, true, true, false);
	return true;
}


MemBufferCollection::tMemBufferPtr	getSingleFrame(Grabber& gr, tColorformatEnum type)
{
	smart_ptr<FrameHandlerSink> pHandlerSink = FrameHandlerSink::create(type,1);//The FrameHandlerSink is the SinkType used to grab (copy) frames from the image stream.
	pHandlerSink->setSnapMode(true);//snap or grab  mode

	gr.setSinkType(pHandlerSink);

	gr.startLive(false);
	Sleep(250); // give the device time to adjust automatic settings i.e. auto exposure
	pHandlerSink->snapImages(1, 2000);//多少张拷贝，不能超过多少秒Queues up a snap job, thus allowing a number of frames to be copied into the MemBufferCollection. 
	gr.stopLive();

	// get pointer to the image data
	return pHandlerSink->getLastAcqMemBuffer();//Returns the MemBuffer, in which the last frame was fully copied
}

int main(int argc, char* argv[])
{

DShowLib::InitLibrary();

Grabber grabberR;
Grabber grabberL;

if (!openDeviceFromFile(grabberR,"lastSelectedDeviceState1.xml"))
{
	return 1;
}


if (!openDeviceFromFile(grabberL, "lastSelectedDeviceState2.xml"))
{
	return 1;
}
grabberL.setOverlayBitmapPathPosition(ePP_NONE);



MemBufferCollection::tMemBufferPtr pActiveBufR = getSingleFrame(grabberR, eRGB32);

MemBufferCollection::tMemBufferPtr pActiveBufL = getSingleFrame(grabberL, eRGB32);

return 0;
}
