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

	InitMarksReconstruct();//�������������궨������

	while (1)
	{
		static DShowLib::Grabber::tMemBufferPtr pLeft;
		static DShowLib::Grabber::tMemBufferPtr pRight;
		Mat  leftGray, rightGray;
		vector<Point2d> rightExtrMarks;
		vector<Point2d> leftExtrMarks;
		vector<Point3d> marks3d;


		if (GetImage(pLeft, pRight, leftGray, rightGray))//��ȡͼ��ͼ��Ԥ����
		{
			AffInMoment(leftGray, leftExtrMarks);//������ȡ

			AffInMoment(rightGray, rightExtrMarks);

		}

		if (rightExtrMarks.size() >= 3 && leftExtrMarks.size() == 4)

		{
			Registor(rightExtrMarks, leftExtrMarks);
		}//����ƥ��

		if (rightExtrMarks.size() == 4 && leftExtrMarks.size() >=3)

		{
			Registor(leftExtrMarks, rightExtrMarks);
		}//����
		

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
			restructMarks(marks3d);//��Ϣ��ʧ����µģ����١�

		}
	}

		return  0;
}
   