
#include"CameraSptr.h"
#include <WinDef.h>


//using namespace _DSHOWLIB_NAMESPACE;

std::shared_ptr<Grabber>grabberR = std::make_shared<Grabber>();
std::shared_ptr<Grabber>grabberL = std::make_shared<Grabber>();

//bool StartCamera()
//{
//	if (grabberR->startLive(false) &&
//		grabberL->startLive(false))
//	{
//		//std::cout << 1111111111 << std::endl;
//		return true;
//	}
//	printf("Error in file:Camera.cpp,function:StartCamera, start camera failed!\n");
//	return false;
//}

//获取图像
//bool GetImageBuffer(Grabber::tMemBufferPtr* bufferR, Grabber::tMemBufferPtr* bufferL)
//{
//	Error err = pSinkR->snapImages(1);
//	if (err.isError())
//	{
//		printf("%s\n", err.c_str());
//		return false;
//	}
//	err = pSinkL->snapImages(1);
//	if (err.isError())
//	{
//		printf("%s\n", err.c_str());
//		return false;
//	}
//
//	*bufferR = pSinkR->getLastAcqMemBuffer();//复制内存
//	*bufferL = pSinkL->getLastAcqMemBuffer();
//
//	return true;
//}

//void SuspendCamera()
//{
//	grabberR->suspendLive();
//	grabberL->suspendLive();
//}
//
//
//void CloseCamera()
//{
//	grabberR->stopLive();
//	grabberL->stopLive();
//}



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

 MemBufferCollection::tMemBufferPtr	getSingleFrame(Grabber& gr, tColorformatEnum type)
 {
	 smart_ptr<FrameHandlerSink> pHandlerSink = FrameHandlerSink::create(type, 10);//The FrameHandlerSink is the SinkType used to grab (copy) frames from the image stream.
	 pHandlerSink->setSnapMode(true);//snap or grab  mode

	 gr.setSinkType(pHandlerSink);

	 gr.startLive(false);
	 Sleep(250); // give the device time to adjust automatic settings i.e. auto exposure
	 pHandlerSink->snapImages(1, 2000);//多少张拷贝，不能超过多少秒Queues up a snap job, thus allowing a number of frames to be copied into the MemBufferCollection. 
	 gr.stopLive();

	 // get pointer to the image data
	 return pHandlerSink->getLastAcqMemBuffer();//Returns the MemBuffer, in which the last frame was fully copied
 }