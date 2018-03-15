
#include<iostream>
#include <fstream> 
#include <iterator>  
#include <vector> 

#include "MarksConstruction.h"
#include "GetImage.h"
#include  "ThreeDimPoint.h"  
using namespace cv;
using namespace std;


//左右相机参数，经过matlab处理
//const string LEFT_FILE_NAME = "HL.xml";//注意这个地方怎么写
//const string  RIGHT_FILE_NAME = "HR.xml";
static Mat ML(3, 4, CV_64FC1);
static Mat MR(3, 4, CV_64FC1);


//计算针尖坐标中使用的变量
static Mat K(4, 3, CV_64FC1);//kX=l
static Mat L(4, 1, CV_64FC1);
//计算中间变量，声明为全局，避免申请和释放的时间消耗
static Mat m34(3, 4, CV_64FC1);
static Mat m33(3, 3, CV_64FC1);
static Mat m31(3, 1, CV_64FC1);
static  Mat cameraMatrixR(3, 3, CV_32FC1);
/*
* 初始化相机
* 标定参数及相机设置
*/
static void  WriteDate()
{
	FileStorage fs1("HL.xml", FileStorage::READ);
	fs1["HL"] >> ML;

	FileStorage fs2("HR.xml", FileStorage::READ);
	fs2["HR"] >> MR;

}
void InitMarksReconstruct()
{
	//初始化获取图像相关设备
	InitGetImages();


	//初始化相机标定内参和外参
	WriteDate();

}


/*
* 计算空间位置
* plx: 左摄像机中X坐标
* ply：左摄像机中Y坐标
* prx：右摄像机中X坐标
* pry：右摄像机中Y坐标
* out3D：double [3] 数组，表示空间坐标x，y，z，该坐标相对于相机标定原点。
*/
bool GetMark3D(double plx, double ply, double prx, double pry, Point3d &out3d)
{

	K.at<double>(0, 0) = plx*ML.at<double>(2, 0) - ML.at<double>(0, 0);
	K.at<double>(0, 1) = plx*ML.at<double>(2, 1) - ML.at<double>(0, 1);
	K.at<double>(0, 2) = plx*ML.at<double>(2, 2) - ML.at<double>(0, 2);
	//(1,0:3)
	K.at<double>(1, 0) = ply*ML.at<double>(2, 0) - ML.at<double>(1, 0);
	K.at<double>(1, 1) = ply*ML.at<double>(2, 1) - ML.at<double>(1, 1);
	K.at<double>(1, 2) = ply*ML.at<double>(2, 2) - ML.at<double>(1, 2);
	//(2,0:3)
	K.at<double>(2, 0) = prx*MR.at<double>(2, 0) - MR.at<double>(0, 0);
	K.at<double>(2, 1) = prx*MR.at<double>(2, 1) - MR.at<double>(0, 1);
	K.at<double>(2, 2) = prx*MR.at<double>(2, 2) - MR.at<double>(0, 2);
	//(3,0:3)
	K.at<double>(3, 0) = pry*MR.at<double>(2, 0) - MR.at<double>(1, 0);
	K.at<double>(3, 1) = pry*MR.at<double>(2, 1) - MR.at<double>(1, 1);
	K.at<double>(3, 2) = pry*MR.at<double>(2, 2) - MR.at<double>(1, 2);

	//create matrix L (0:3,0)
	L.at<double>(0, 0) = ML.at<double>(0, 3) - plx*ML.at<double>(2, 3);
	L.at<double>(1, 0) = ML.at<double>(1, 3) - ply*ML.at<double>(2, 3);
	L.at<double>(2, 0) = MR.at<double>(0, 3) - prx*MR.at<double>(2, 3);
	L.at<double>(3, 0) = MR.at<double>(1, 3) - pry*MR.at<double>(2, 3);

	//calculate 3d positoin of mark center
	m34 = K.t();
	m33 = m34 * K;
	m33 = m33.inv();
	m31 = m33 * m34 * L;

	//cout << m31 <<endl;
	//set the return value;
	out3d.x = m31.at<double>(0, 0);//不能对空指针进行操作
	out3d.y = m31.at<double>(1, 0);
	out3d.z = m31.at<double>(2, 0);

	cout << "三维重建结果"<<out3d.x << "  " << out3d.y << "  " << out3d.z<<endl;
	return true;
}



//信息丢失情况下，三维重建
void restructMarks(vector<Point3d>&marks3d)//主要是给结构体赋值
{

	
		Point3d miss;
		for (auto i = marks3d.begin(); i != marks3d.end(); i++)
			cout << "只重建了三个" << *i << endl;

		miss = OtherThree(marks3d[0], marks3d[1], marks3d[2]);

		marks3d.push_back(miss);


}

