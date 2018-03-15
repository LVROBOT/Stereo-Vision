
#include"Camera.h"
#include <WinDef.h>

std::shared_ptr<Grabber>grabberR = std::make_shared<Grabber>();
std::shared_ptr<Grabber>grabberL = std::make_shared<Grabber>();

static smart_ptr<FrameHandlerSink> pSinkR;
static smart_ptr<FrameHandlerSink> pSinkL;

//从文件中打开摄像机，设定摄像机的参数
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

bool OpenCamera()
{
	//初始化库
	DShowLib::InitLibrary();

	if (!openDeviceFromFile(*grabberR, "lastSelectedDeviceState2.xml"))//从文件里打开摄像机
	{
		printf("Init right camera failed!");
		printf("Error: %s\n", grabberR->getLastError().c_str());
		return false;
	}


	if (!openDeviceFromFile(*grabberL, "lastSelectedDeviceState1.xml"))
	{
		printf("Init left camera failed!");
		printf("Error: %s\n", grabberR->getLastError().c_str());
		return false;
	}

	//set Grabber sinktype
	pSinkR = FrameHandlerSink::create(eRGB24, 10);
	pSinkR->setSnapMode(true);
	grabberR->setSinkType(pSinkR);

	pSinkL = FrameHandlerSink::create(eRGB24, 10);
	pSinkL->setSnapMode(true);
	grabberL->setSinkType(pSinkL);

	if (!grabberR->prepareLive(false))
	{
		printf("Error: %s\n", grabberR->getLastError().c_str());
		return false;
	}
	if (!grabberL->prepareLive(false))
	{
		printf("Error: %s\n", grabberL->getLastError().c_str());
		return false;
	}

	return true;

}


bool GetImageBuffer(MemBufferCollection::tMemBufferPtr * bufferR, MemBufferCollection::tMemBufferPtr *bufferL)
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


bool StartCamera()//开启Live模式
{
	if (grabberR->startLive(false) &&
		grabberL->startLive(false))
	{

		return true;
	}
	printf("Error in file:Camera.cpp,function:StartCamera, start camera failed!\n");
	return false;
}

void SuspendCamera()//挂起相机
{
	grabberR->suspendLive();
	grabberL->suspendLive();
}

void CloseCamera()//关闭相机
{
	if (grabberR != NULL)
	{
		grabberR->stopLive();
		grabberR->closeDev();
	}
	if (grabberL != NULL)
	{
		grabberL->stopLive();
		grabberL->closeDev();

	}
}


