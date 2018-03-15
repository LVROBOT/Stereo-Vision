
#ifndef _REGISTER_H_
#define _REGISTER_H_

#include <opencv2/opencv.hpp> 
#include <cv.h>
#include"Camera.h"
using namespace cv;


void Registor(vector<Point2d> & lessVec, vector<Point2d> & moreVec);


#endif