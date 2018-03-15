#ifndef _MarksConstruction_H_
#define _MarksConstruction_H_

#include <opencv2/opencv.hpp> 
#include <cv.h>
#include <highgui.h>
#include "GetImage.h"

using namespace cv;
/*
* ��ʼ�����
* �궨�������������
*/
void InitMarksReconstruct();

/*
* ����ռ�λ��
* plx: ���������X����
* ply�����������Y����
* prx�����������X����
* pry�����������Y����
* out3D��double [3] ���飬��ʾ�ռ�����x��y��z�����������������궨ԭ�㡣
*/
bool GetMark3D(double plx, double ply, double prx, double pry, Point3d &out3d);

void restructMarks(vector<Point3d>&marks3d);

#endif 