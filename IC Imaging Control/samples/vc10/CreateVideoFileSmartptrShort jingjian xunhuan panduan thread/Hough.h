#pragma once
#include <stdio.h>
#include <cv.h>
#include <highgui.h>
#include <fstream>//������ļ���

#include <windows.h>
#include <conio.h>
#include <iostream>
#include <tisudshl.h>
#include "../Common/CmdHelper.h"


using namespace _DSHOWLIB_NAMESPACE;

using namespace std;
using namespace cv;

extern IplImage* leftdst ;
extern IplImage* rightdst ;

void SWAP(CvPoint &x, CvPoint &y);
void sort(vector<CvPoint> &vecTest, int n);//ѡ������

void Bismooth(MemBufferCollection::tMemBufferPtr& Pleft, MemBufferCollection::tMemBufferPtr & Pright);
void ExCircles(CvArr* dstleft, CvArr* dstright);

void SaveCircles(CvArr* dst, const char *Filename, CvSeq* circles);