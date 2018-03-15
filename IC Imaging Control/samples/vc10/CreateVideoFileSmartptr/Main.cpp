

#include"CameraSptr.h"
#include <WinDef.h>
#include <cv.h>
#include <highgui.h>

using namespace cv;
//
Grabber::tMemBufferPtr  Pleft;
//
Grabber::tMemBufferPtr Pright;
//
/*IplImage* leftRGB=NULL;
IplImage* rightRGB=NULL;

IplImage* leftImage = NULL;
IplImage* rightImage = NULL*/;

int main(int argc, char* argv[])

{
	DShowLib::InitLibrary();

	if (!openDeviceFromFile(*grabberR, "lastSelectedDeviceState1.xml"))
	{
		return 1;
	}


	if (!openDeviceFromFile(*grabberL, "lastSelectedDeviceState2.xml"))
	{
		return 1;
	}
	

	//set Grabber sinktype
	pSinkR = FrameHandlerSink::create(eRGB32, 10);//////////////////////此处自带循环
	pSinkR->setSnapMode(true);
	grabberR->setSinkType(pSinkR);
	pSinkL = FrameHandlerSink::create(eRGB32, 10);
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

	StartCamera();


	//GetImageBuffer(&Pright, &Pleft);/////////////////有问题
	

	//leftRGB = cvCreateImage(cvSize(960,1280), IPL_DEPTH_8U, 1);
	//rightRGB = cvCreateImage(cvSize(960,1280), IPL_DEPTH_8U, 1);

	//leftImage = cvCreateImage(cvSize(960,1280), IPL_DEPTH_8U, 1);
	//rightImage = cvCreateImage(cvSize(960,1280), IPL_DEPTH_8U, 1);

	//leftRGB->imageData = (char*)(Pleft->getPtr());/////////////
	//rightRGB->imageData = (char*)(Pright->getPtr());/////////////

	//cvCvtColor(leftRGB, leftImage,CV_RGB2GRAY);
	//
	//cvCvtColor(rightRGB, rightImage, CV_RGB2GRAY);

	//cvFlip(leftImage);

	//cvFlip(leftImage);

	SuspendCamera();
	CloseCamera();
	return 0;
}
