/*
* 摄像机驱动程序
* 初始化相机，从相机读取图像，挂起相机，关闭相机
* 
* hby.2013.03.22
*/


#include "Camera.h"
#include <WinDef.h>
//using namespace DShowLib;
using namespace _DSHOWLIB_NAMESPACE;

static Grabber* grabberR;
static Grabber* grabberL;
static tFrameHandlerSinkPtr pSinkR;
static tFrameHandlerSinkPtr pSinkL;


bool OpenCamera()
{
	//load and init library
	if (!DShowLib::InitLibrary())//////////InitLibrary( "ISB3200016679" )
	{
		return false;
	}
	 
	atexit( DShowLib::ExitLibrary );

	//DShowLib::InitLibrary();

	//set camera parameters by loading setting file 
	//open device
	grabberR = new Grabber();


		if (!grabberR->openDev(0x47514598))
	{
		printf("Init left camera failed!");
		printf( "Error: %s\n", grabberR->getLastError().c_str() );
		return false;
	}
	grabberR->setFrameRate(3);
	grabberR->setProperty(VideoProcAmp_WhiteBalance, false);
	Grabber::tVidFmtListPtr formates = grabberR->getAvailableVideoFormats();
	
	grabberR->setVideoFormat(grabberR->getAvailableVideoFormats()->at(86));


	grabberL = new Grabber();
	if (!grabberL->openDev(0x47514267))
	{
		printf("Init left camera failed!");
		printf( "Error: %s\n", grabberL->getLastError().c_str() );
		return false;
	}
	grabberL->setFrameRate(3);
	grabberL->setProperty(VideoProcAmp_WhiteBalance, false);
	grabberL->setVideoFormat(grabberL->getAvailableVideoFormats()->at(86));/////////////////自己查找

	//set Grabber sinktype
	pSinkR = FrameHandlerSink::create( eRGB32, 10 );//////////////////////此处自带循环
	pSinkR->setSnapMode(true);
	grabberR->setSinkType(pSinkR);    
	pSinkL = FrameHandlerSink::create( eRGB32, 10 );
	pSinkL->setSnapMode(true);
	grabberL->setSinkType(pSinkL);

	if( !grabberR->prepareLive( false ) )
	{
		printf( "Error: %s\n", grabberR->getLastError().c_str() );
		return false;
	}
	if( !grabberL->prepareLive( false ) )
	{
		printf( "Error: %s\n", grabberL->getLastError().c_str() );
		return false;
	}

	return true;

}

bool StartCamera()
{
	if (grabberR->startLive(false) && 
		grabberL->startLive(false))
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
	grabberR->suspendLive();
	grabberL->suspendLive();
}


//void CloseCamera()
//{
//	if (grabberR != NULL)
//	{
//		grabberR->closeDev();
//		
//	}
//	if (grabberL != NULL)
//	{
//		grabberL->closeDev();
//	
//	}
//		delete grabberL;
//	delete grabberR;
//}

void CloseCamera()
{
	
		grabberR->stopLive();
		//delete grabberR;
		grabberL->stopLive();
	  // delete grabberL;
	
}



//int main()
//{
//
//	OpenCamera();
//
//	 StartCamera();
//	 SuspendCamera();
//     CloseCamera();
//	return 0;
//}