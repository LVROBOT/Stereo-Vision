/*
* ��ȡ���ͼ�񣬲�ת��Ϊopencv��ʽ
* �������ͼƬ��ʽ����ʼ��opencvͼ�����ʽ
*  2017.5.16
*/

#ifndef _GETIMAGE_H_
#define _GETIMAGE_H_
#include <opencv2/opencv.hpp> 
#include <cv.h>
#include"Camera.h"
using namespace cv;
/*
* ��ȡͼ��
*/
bool GetImage(DShowLib::Grabber::tMemBufferPtr & pLeft, DShowLib::Grabber::tMemBufferPtr &pRight,Mat & leftGray, Mat& rightGray);//����ͼ���������Ϣ


void AffInMoment(Mat & image, vector<Point2d> & extrMarks);


/*
* Ϊ�������ȡͼ������׼��
* ���øú����󣬿���ʹ��GetImage��ȡͼ��
*/
void InitGetImages();

/*
* ����Ҫ����ͼ��֮�󣬵��øú��������Թر����
*
*/
void EndGetImages();

#endif