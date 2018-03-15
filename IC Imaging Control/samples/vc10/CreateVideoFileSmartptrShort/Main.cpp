
#include"Hough.h"
#include"CameraSptr.h"
#include <WinDef.h>
#include <cv.h>
#include <highgui.h>

using namespace cv;




int main(int argc, char* argv[])

{
	DShowLib::InitLibrary();/////////////

	if (!openDeviceFromFile(*grabberR, "lastSelectedDeviceState2.xml"))///////////////
	{
		printf("Init right camera failed!");
		printf("Error: %s\n", grabberR->getLastError().c_str());
		return false;
	}


	if (!openDeviceFromFile(*grabberL, "lastSelectedDeviceState1.xml"))///////////////////����һ��������
	{
		printf("Init left camera failed!");
		printf("Error: %s\n", grabberR->getLastError().c_str());
		return false;
	}
	

	//set Grabber sinktype
	//pSinkR = FrameHandlerSink::create(eRGB32, 10);//////////////////////�˴��Դ�ѭ��
	//pSinkR->setSnapMode(true);
	//grabberR->setSinkType(pSinkR);
	//pSinkL = FrameHandlerSink::create(eRGB32, 10);
	//pSinkL->setSnapMode(true);
	//grabberL->setSinkType(pSinkL);

	//if (!grabberR->prepareLive(false))
	//{
	//	printf("Error: %s\n", grabberR->getLastError().c_str());
	//	return false;
	//}
	//if (!grabberL->prepareLive(false))
	//{
	//	printf("Error: %s\n", grabberL->getLastError().c_str());
	//	return false;
	//}

	Pleft = getSingleFrame(*grabberR, eRGB24);//////////////////��ʽ���
	Pright = getSingleFrame(*grabberL, eRGB24);///////////////////


	leftRGB->imageData = (char*)(Pleft->getPtr());//�ڲ���������ָ�룬����_UDSHL_EXP_API BYTE*	
	rightRGB->imageData = (char*)(Pright->getPtr());/////////////

	cvCvtColor(leftRGB, leftImage, CV_RGB2GRAY);/////////////////ͨ��������������
	cvCvtColor(rightRGB, rightImage, CV_RGB2GRAY);////////////////

	

	Bismooth(leftImage, leftdst);
	Bismooth(rightImage, rightdst);

	

	CvSeq* circlesLeft = cvHoughCircles(leftdst, storageLeft, CV_HOUGH_GRADIENT, 1, leftdst->width / 15, 100, 15, 15, 20);
	CvSeq* circlesRight = cvHoughCircles(rightdst, storageRight, CV_HOUGH_GRADIENT, 1, leftdst->width / 15, 100, 15, 15, 20);

	DrawCircles(leftdst,circlesLeft, "left.txt");
	DrawCircles(rightdst, circlesRight, "right.txt");

	/*cvFlip(leftImage);

	cvFlip(rightImage);*/

	//cvNamedWindow("c", 1);
	//cvShowImage("c", rightRGB);
//	cvNamedWindow("f", 1);
	//cvShowImage("f",rightdst);

	cvWaitKey(0);







	




	/*cvSaveImage("22.bmp", leftRGB);
	cvSaveImage("33.bmp", leftImage);
	Pleft->save("4.bmp");*/

	/*cvReleaseImage(&leftRGB);

	cvReleaseImage(&rightRGB);

	cvReleaseImage(&leftImage);
	cvReleaseImage(&rightImage);*/

	return 0;
}
