#pragma once
#include <stdio.h>
#include <cv.h>
#include <highgui.h>
#include <fstream>//保存成文件用

using namespace std;
using namespace cv;

extern IplImage* leftRGB ;
extern IplImage* rightRGB ;

extern IplImage* leftImage ;
extern IplImage* rightImage ;

extern IplImage* leftdst ;
extern IplImage* rightdst ;

extern CvMemStorage* storageLeft;
extern CvMemStorage* storageRight;


void SWAP(CvPoint &x, CvPoint &y);
void sort(vector<CvPoint> &vecTest, int n);//选择排序

void Bismooth(const CvArr* src, CvArr* dst);
void DrawCircles(CvArr* dst, CvSeq* circles, const char *_Filename);

