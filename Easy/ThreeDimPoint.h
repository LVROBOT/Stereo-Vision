//针对三维点的各种计算
#pragma once
#include <opencv2/opencv.hpp> 
#include <cv.h>
#include <highgui.h>
#include <vector>
using namespace cv;

void print(const Point3d &p);//向量的大小
double pointDistance(Point3d p1, Point3d p2);
vector<double> pointAngle(Point3d p1, Point3d p2, Point3d p3);
double area(Point3d p1, Point3d p2, Point3d p3);
double LongDis(Point3d p1, Point3d p2, Point3d p3);
string MissFind(Point3d p1, Point3d p2, Point3d p3);
vector<Point3d> PointName(Point3d p1, Point3d p2, Point3d p3);//abcd各自对应的坐标
Point3d  OtherThree(Point3d p1, Point3d p2, Point3d p3);
vector <double> get_panel(Point3d p1, Point3d p2, Point3d p3);
