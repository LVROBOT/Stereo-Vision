#ifndef _MarksConstruction_H_
#define _MarksConstruction_H_

#include <opencv2/opencv.hpp> 
#include <cv.h>
#include <highgui.h>
#include "GetImage.h"

using namespace cv;
/*
* 初始化相机
* 标定参数及相机设置
*/
void InitMarksReconstruct();

/*
* 计算空间位置
* plx: 左摄像机中X坐标
* ply：左摄像机中Y坐标
* prx：右摄像机中X坐标
* pry：右摄像机中Y坐标
* out3D：double [3] 数组，表示空间坐标x，y，z，该坐标相对于相机标定原点。
*/
bool GetMark3D(double plx, double ply, double prx, double pry, Point3d &out3d);

void restructMarks(vector<Point3d>&marks3d);

#endif 