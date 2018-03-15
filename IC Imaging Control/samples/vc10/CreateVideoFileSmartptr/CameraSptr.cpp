
#include"CameraSptr.h"
#include <WinDef.h>


//using namespace _DSHOWLIB_NAMESPACE;

std::shared_ptr<Grabber>grabberR = std::make_shared<Grabber>();
std::shared_ptr<Grabber>grabberL = std::make_shared<Grabber>();




bool StartCamera()
{
	if (grabberR->startLive(false) &&
		grabberL->startLive(false))
	{
		//std::cout << 1111111111 << std::endl;
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
	grabberR->suspendLive();
	grabberL->suspendLive();
}


void CloseCamera()
{
	grabberR->stopLive();
	grabberL->stopLive();
}



 bool	openDeviceFromFile(_DSHOWLIB_NAMESPACE::Grabber& gr, const std::string& devStateFilename)
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
	gr.setOverlayBitmapPathPosition(ePP_NONE);
	return true;
}