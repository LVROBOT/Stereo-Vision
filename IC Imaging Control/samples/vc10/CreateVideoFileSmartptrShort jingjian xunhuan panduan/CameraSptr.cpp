
#include"CameraSptr.h"
#include <WinDef.h>


std::shared_ptr<Grabber>grabberR = std::make_shared<Grabber>();
std::shared_ptr<Grabber>grabberL = std::make_shared<Grabber>();

static smart_ptr<FrameHandlerSink> pSinkR;
static smart_ptr<FrameHandlerSink> pSinkL;

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

	 DShowLib::InitLibrary();/////////////

	 if (!openDeviceFromFile(*grabberR, "lastSelectedDeviceState2.xml"))///////////////
	 {
		 printf("Init right camera failed!");
		 printf("Error: %s\n", grabberR->getLastError().c_str());
		 return false;
	 }


	 if (!openDeviceFromFile(*grabberL, "lastSelectedDeviceState1.xml"))///////////////////放入一个函数中
	 {
		 printf("Init left camera failed!");
		 printf("Error: %s\n", grabberR->getLastError().c_str());
		 return false;
	 }


	 pSinkR = FrameHandlerSink::create(eRGB24, 10);//////////////////////此处自带循环
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

	* bufferR = pSinkR->getLastAcqMemBuffer();//复制内存
	* bufferL = pSinkL->getLastAcqMemBuffer();

	 return true;
 }


 bool StartCamera()
 {
	 if (grabberR->startLive(false)
		 && grabberL->startLive(false))
	 {
		Sleep(250);
		 return true;
	 }
	 printf("Error in file:Camera.cpp,function:StartCamera, start camera failed!\n");
	 return false;
 }

 void SuspendCamera()
 {
	 grabberR->suspendLive();
	 grabberL->suspendLive();
 }

 void CloseCamera()
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