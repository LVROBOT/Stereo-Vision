#include <boost/timer.hpp>
#include <opencv2/opencv.hpp> 
#include <cv.h>
#include <highgui.h>
#include <Windows.h>
#include <iostream>
#include <vector>
#include "GetImage.h"
#include "Camera.h"

using namespace cv;
using namespace std;


/*
* 为从相机获取图像做好准备
* 调用该函数后，可以使用GetImage获取图像
*/
void InitGetImages()
{
	OpenCamera();
	StartCamera();
	//Sleep(500);
}

/*
* 不需要调用图像之后，调用该函数，可以关闭相机
*
*/
void EndGetImages()
{
	CloseCamera();
}


/*图像采集及图像预处理*/
bool GetImage(DShowLib::Grabber::tMemBufferPtr & pLeft, DShowLib::Grabber::tMemBufferPtr &pRight, Mat & leftGray, Mat& rightGray)//左右图像的搜索信息
{

	if (!GetImageBuffer(&pRight, &pLeft))
	{
		printf("error in file:GetImageFromCamera.cpp function:InitOpenCVmats\n");
		return false;
	}

	Size size(pLeft->getBitmapInfoHeader()->biWidth, pLeft->getBitmapInfoHeader()->biHeight);

	Mat leftRGB = Mat(size, CV_8UC3);//RGB32为4通道，多一个A通道 ，表示透明度；
	Mat rightRGB = Mat(size, CV_8UC3);

	leftRGB.data = (uchar*)(pLeft->getPtr());
	rightRGB.data = (uchar*)(pRight->getPtr());


	cvtColor(leftRGB, leftGray, CV_RGB2GRAY);//没有A没有透明度
	cvtColor(rightRGB, rightGray, CV_RGB2GRAY);

	/*Size ResImgSiz = Size(1280*0.5, 960*0.5);
	resize(leftGray, leftGray, ResImgSiz, CV_INTER_CUBIC);

	resize(rightGray, rightGray, ResImgSiz, CV_INTER_CUBIC);*/
	GaussianBlur(leftGray, leftGray, Size(25, 25), 0, 0);	//高斯滤波

	GaussianBlur(rightGray, rightGray, Size(25, 25), 0, 0);	//高斯滤波

	threshold(leftGray, leftGray, 130, 255, THRESH_BINARY);//二值化

	threshold(rightGray, rightGray, 130, 255, THRESH_BINARY);//二值化

	/*imshow("left", leftGray);
	imshow("right", rightGray);
	waitKey(0);*/
	return true;

}

/*
基于轮廓的仿射不变矩特征提取,提取标志球的圆心像素坐标
*/

void AffInMoment(Mat & image, vector<Point2d> & extrMarks)
{
	vector< vector<Point> >contours;
	vector<Vec4i>hierarchy;
	CvBox2D box;
	unsigned int i;
	findContours(image, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);//CV_RETR_CCOMP 所有的轮廓 ; CV_RETR_EXTERNAL 最外面的轮廓
	for (i = 0; i < contours.size(); i++)
	{
		Moments moment;
		moment = moments(contours[i], false);//基于轮廓的不变距
		double u00 = moment.m00; double u01 = moment.m01; double u10 = moment.m10;
		double u20 = moment.mu20; double u11 = moment.mu11; double u02 = moment.mu02;
		double u30 = moment.mu30; double u21 = moment.mu21; double u12 = moment.mu12; double u03 = moment.mu03;//原点距和中心距
		double I1 = (u02*u20 - u11*u11) / pow(u00, 4);		//一阶矩
		double I2 = (u30*u30*u03*u03 - 6 * u30*u12*u21*u03 + 4 * u30*pow(u12, 3) + 4 * u03*pow(u21, 3) - 3 * u21*u21*u12*u12) / pow(u00, 10);
		double I3 = (u20*(u21*u03 - u12*u12) - u11*(u30*u03 - u21*u12) + u02*(u30*u12 - u21*u21)) / pow(u00, 7);
		double Ia = abs(I1 - 0.006332) - 0.0003; //不变矩阈值判断 与标准不变矩值比较
		double Ib = abs(I2) - 0.00001;
		double Ic = abs(I3) - 0.00001;

		if (Ia <= 0 && Ib<0 && Ic<0)
		{
			box = fitEllipse(contours[i]);	//椭圆曲线拟合
			if (box.size.width>10 && box.size.height>10)
			{
				Point2d center;
				center.x = int(box.center.x);		//图像缩放
				center.y = int(box.center.y);
				//cout << "  高  " << center.x << " 宽   " << center.y;
				extrMarks.push_back(center);
				ellipse(image, box, Scalar(0, 250, 0), 0.2);	//画出椭圆
				circle(image, box.center, 1, Scalar(250, 0, 0), 0.01, 8);	//画出椭圆心
			}
		}
	}

}


