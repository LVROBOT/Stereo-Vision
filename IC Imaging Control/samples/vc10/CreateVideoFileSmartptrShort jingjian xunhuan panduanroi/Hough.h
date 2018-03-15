#pragma once
#include <stdio.h>
#include <cv.h>
#include <highgui.h>
#include <fstream>//保存成文件用

#include <windows.h>
#include <conio.h>
#include <iostream>
#include <tisudshl.h>
#include "../Common/CmdHelper.h"


using namespace _DSHOWLIB_NAMESPACE;

using namespace std;
using namespace cv;

extern IplImage* leftdst ;//尽量少定义全局变量
extern IplImage* rightdst ;

void SWAP(CvPoint &x, CvPoint &y);
void sort(vector<CvPoint> &vecTest, int n);//选择排序

void Bismooth(MemBufferCollection::tMemBufferPtr& Pleft, MemBufferCollection::tMemBufferPtr & Pright);
void ExCircles(CvArr* dstleft, CvArr* dstright);

void SaveCircles(const char *Filename, vector<CvPoint>  &vecTest);
void MyROI(IplImage* dst, vector<CvPoint> &vecTest);