#define _WIN32_WINNT 0x0500

#include <windows.h>
#include <conio.h>
#include <iostream>
#include <tisudshl.h>

#include "../Common/CmdHelper.h"

using namespace _DSHOWLIB_NAMESPACE;

static tFrameHandlerSinkPtr pSinkR;
static tFrameHandlerSinkPtr pSinkL;
Grabber grabberR;
Grabber grabberL;


bool StartCamera()
{
	if (grabberR.startLive(false) &&
		grabberL.startLive(false))
	{
		return true;
	}
	printf("Error in file:Camera.cpp,function:StartCamera, start camera failed!\n");
	return false;
}

//获取图像
bool GetImageBuffer(Grabber::tMemBufferPtr* bufferR, Grabber::tMemBufferPtr* bufferL)
{
	Error err = pSinkR->snapImages(1);
	if (err.isError())
	{
		printf("%s\n", err.c_str());
		return false;
	}
	err = pSinkL->snapImages(1);
	if (err.isError())
	{
		printf("%s\n", err.c_str());
		return false;
	}

	*bufferR = pSinkR->getLastAcqMemBuffer();//复制内存
	*bufferL = pSinkL->getLastAcqMemBuffer();

	return true;
}

void SuspendCamera()
{
	grabberR.suspendLive();
	grabberL.suspendLive();
}


void CloseCamera()
{
	grabberR.stopLive();
	grabberL.stopLive();
}



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


int main(int argc, char* argv[])
{

	DShowLib::InitLibrary();
	
	if (!openDeviceFromFile(grabberR, "lastSelectedDeviceState1.xml"))
	{
		return 1;
	}


	if (!openDeviceFromFile(grabberL, "lastSelectedDeviceState2.xml"))
	{
		return 1;
	}
	grabberL.setOverlayBitmapPathPosition(ePP_NONE);

	//set Grabber sinktype
	pSinkR = FrameHandlerSink::create(eRGB32, 10);//////////////////////此处自带循环
	pSinkR->setSnapMode(true);
	grabberR.setSinkType(pSinkR);
	pSinkL = FrameHandlerSink::create(eRGB32, 10);
	pSinkL->setSnapMode(true);
	grabberL.setSinkType(pSinkL);

	if (!grabberR.prepareLive(false))
	{
		printf("Error: %s\n", grabberR.getLastError().c_str());
		return false;
	}
	if (!grabberL.prepareLive(false))
	{
		printf("Error: %s\n", grabberL.getLastError().c_str());
		return false;
	}


	StartCamera();
	 SuspendCamera();
	 CloseCamera();

	return 0;
}
