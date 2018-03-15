#include<iostream>
#include <fstream> 
#include <vector> 
#include "MarksConstruction.h" 
#include "register.h"
#include "GetImage.h"
using namespace cv;
using namespace std;

int main()
{

	InitMarksReconstruct();//打开摄像机，导入标定参数；

	while (1)
	{
		static DShowLib::Grabber::tMemBufferPtr pLeft;
		static DShowLib::Grabber::tMemBufferPtr pRight;
		Mat  leftGray, rightGray;
		vector<Point2d> rightExtrMarks;
		vector<Point2d> leftExtrMarks;
		vector<Point3d> marks3d;


		if (GetImage(pLeft, pRight, leftGray, rightGray))//提取图像，图像预处理
		{
			AffInMoment(leftGray, leftExtrMarks);//特征提取

			AffInMoment(rightGray, rightExtrMarks);

		}

		if (rightExtrMarks.size() >= 3 && leftExtrMarks.size() == 4)

		{
			Registor(rightExtrMarks, leftExtrMarks);
		}//立体匹配

		if (rightExtrMarks.size() == 4 && leftExtrMarks.size() >=3)

		{
			Registor(leftExtrMarks, rightExtrMarks);
		}//立体
		

		if (4 == leftExtrMarks.size() && 4 == rightExtrMarks.size())
		{

			for (int i = 0; i < 4; i++)
			{
				Point3d  np3d;
				if (GetMark3D(leftExtrMarks[i].x, leftExtrMarks[i].y, rightExtrMarks[i].x, rightExtrMarks[i].y, np3d))
					marks3d.push_back(np3d);
			}
		}


		if ((4 == leftExtrMarks.size() && 3 == rightExtrMarks.size()) || (3 == leftExtrMarks.size() && 4== rightExtrMarks.size()))
		{

			for (int i = 0; i < 3; i++)
			{
				Point3d  np3d;
				if (GetMark3D(leftExtrMarks[i].x, leftExtrMarks[i].y, rightExtrMarks[i].x, rightExtrMarks[i].y, np3d))
					marks3d.push_back(np3d);
			}
		}



		if (3 == marks3d.size())
		{
			restructMarks(marks3d);//信息丢失情况下的，跟踪。

		}
	}

		return  0;
}
   