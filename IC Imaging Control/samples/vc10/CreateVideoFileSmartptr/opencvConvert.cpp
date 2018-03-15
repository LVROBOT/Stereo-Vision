#include "opencv2/opencv.hpp"
#include "tisudshl.h"
#include "../Common/CmdHelper.h"//这两个头文件是需要包含的，这样才能进行文件的生成
using namespace cv;
using namespace _DSHOWLIB_NAMESPACE;
int main()
{
	Mat capframe; //得到的图像
	IplImage* rawImage; //旧版的图像
	Grabber grabber;
	tFrameHandlerSinkPtr pSink;
	BYTE* pBuf[1];
	FrameTypeInfo info;
	tMemBufferCollectionPtr pCollection;
	int Height;
	int Width;
	// 图像的类型
	int captype;
	// 图像的通道
	int capchannels;
	//以下就是相机的初始化
	DShowLib::InitLibrary();
	BOOL CameraExist = PathFileExists(L"lastSelectedDeviceState.xml");
	if (!CameraExist)
	{
		setupDeviceFromFile(grabber);
	}
	if (grabber.getAvailableVideoCaptureDevices() == 0)
	{
		return false;
	}

	grabber.loadDeviceStateFromFile("lastSelectedDeviceState.xml");
	//    grabber.saveDeviceStateToFile("lastSelectedDeviceState.xml");
	grabber.setOverlayBitmapPathPosition(ePP_NONE);
	pSink = FrameHandlerSink::create(eY800, 1);

	pSink->setSnapMode(true);

	// Set the sink.
	grabber.setSinkType(pSink);

	// Prepare the live mode, to get the output size if the sink.
	if (!grabber.prepareLive(false))
	{
		std::cerr << "Could not render the VideoFormat into a eY800 sink.";
		return false;
	}
	pSink->getOutputFrameType(info);
	pBuf[0] = new BYTE[info.buffersize];
	pCollection = MemBufferCollection::create(info, 1, pBuf);
	if (pCollection == 0 || !pSink->setMemBufferCollection(pCollection))
	{
		std::cerr << "Could not set the new MemBufferCollection, because types do not match.";
		return false;
	}
	grabber.startLive(false);
	rawImage = cvCreateImage(cvSize(2592, 1944), IPL_DEPTH_8U, 1);
	rawImage->widthStep = 2592;
	rawImage->imageData = (char*)pBuf[0];
	capframe.create(1944, 2592, CV_8U);
	Height = 2592;
	Width = 1944;
	captype = CV_8U;
	capchannels = 1;
	//初始化完毕，下面开始获取一副图像
	pSink->snapImages(1);
	capframe.data = (uchar*)rawImage->imageData;
	//Mat::Mat(rawImage).copyTo(capframe);
	return 1;
}