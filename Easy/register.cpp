
#include <opencv2/opencv.hpp> 
#include <cv.h>
#include <highgui.h>
#include <iostream>
#include <vector>
#include <math.h>
#include <fstream> 
#include "register.h"

using namespace cv;
using namespace std;


   static void SWAP(Point2d &x, Point2d &y)//交换
{

	Point2d t;
	t = x, x = y, y = t;
};

void sort(vector<Point2d> &vecTest)//按照Y的大小选择排序
{
	int i, j, min;
	int n = vecTest.size();
	for (i = 0; i < n - 1; i++){
		min = i;
		for (j = i + 1; j < n; j++)
			if (vecTest[j].y < vecTest[min].y || ((vecTest[j].y == vecTest[min].y) && vecTest[j].x < vecTest[min].x))//判定条件按实际情况修改

				//if (vecTest[j].x < vecTest[min].x )
				min = j;
		SWAP(vecTest[i], vecTest[min]);
	}
};


void sortXB(vector<Point2d> &vecTest)//按照X的大小选择排序
{
	int i, j, min;
	int n = vecTest.size();
	for (i = 0; i < n - 1; i++){
		min = i;
		for (j = i + 1; j < n; j++)
			if (vecTest[j].x < vecTest[min].x || ((vecTest[j].x == vecTest[min].x) ))//判定条件按实际情况修改

				//if (vecTest[j].x < vecTest[min].x )
				min = j;
		SWAP(vecTest[i], vecTest[min]);
	}
};

void sortXM(vector<Point2d> &vecTest)//按照X的大小选择排序
{
	int i, j, max;
	int n = vecTest.size();
	for (i = 0; i < n - 1; i++){
		max = i;
		for (j = i + 1; j < n; j++)
			if (vecTest[j].x > vecTest[max].x || ((vecTest[j].x == vecTest[max].x)))//判定条件按实际情况修改

				//if (vecTest[j].x < vecTest[min].x )
				max = j;
		SWAP(vecTest[i], vecTest[max]);
	}
};


//求解中心点
  static Point2d CenterPoint(const vector<Point2d> &vecPoint)
{
	  Point2d center;
	  for (auto i = vecPoint.begin(); i != vecPoint.end(); ++i)
	  {
		  center.x += (*i).x;
		  center.y += (*i).y;
	  }
	  center.x /= vecPoint.size();
	  center.y /= vecPoint.size();

	  return center;
};


  //分组

  static bool DivGroup(const vector<Point2d> &vecPoint, vector<Point2d> & divideGroup)
  {
	  if (2 >= vecPoint.size())
	  {
		  return false;
	  }


	  Point2d center;
	  center = CenterPoint(vecPoint);
	
	  vector<Point2d> top;
	  vector<Point2d>  bottom;

	  for (auto i = vecPoint.begin(); i != vecPoint.end(); ++i)
	  {
		  if ((*i).y > center.y)
		  {
			  bottom.push_back(*i);
		  }

		  if ((*i).y <= center.y)
		  {
			  top.push_back(*i);
		  }
		
	  }

	  sortXB(bottom);
	  sortXM(top);

	  top.insert(top.end(), bottom.begin(), bottom.end());

	  divideGroup = top;

	 /* for (auto i = divideGroup.begin(); i != divideGroup.end(); ++i)
	  {
		  cout << *i << "  divideGroup"<<endl;
	  }*/

	  return true;
  }


 
  //依次做向量,返回原始的点和向量
  vector<pair<Point2d, Point2d>> Dovector(const vector<Point2d> & divideGroup)
  {

	  vector<pair<Point2d, Point2d>> doVector;
	   for (auto i = divideGroup.begin(); i != divideGroup.end() - 1; ++i)
	   {
	    Point2d temp;
	    temp.x = (*i).x - (*(i+1)).x;
	    temp.y = (*i).y - (*(i+1)).y;
		pair<Point2d, Point2d> a = { *i, temp };
		doVector.push_back(a);
	   }
	   Point2d temp;
	   temp.x = (*(divideGroup.end() - 1)).x - (*divideGroup.begin()).x;
	   temp.y = (*(divideGroup.end() - 1)).y - (*divideGroup.begin()).y;
	   pair<Point2d, Point2d> a = { *(divideGroup.end() - 1), temp };
	   doVector.push_back(a);

	  /* for (auto i = doVector.begin(); i != doVector.end(); ++i)
	    {
		   cout << (*i).first<< " " << (*i).second << endl;
	    }*/
	   return doVector;
  }


  //向量求模
  static double vectorBig( const Point2d & vec)
  {
	  return sqrt(vec.x*vec.x + vec.y*vec.y);
  }

  //向量积

  static double vectorProduct(const Point2d & vecA, const Point2d & vecB)
  {
	  return vecA.x*vecB.x + vecA.y*vecB.y;
  
  }

  //向量夹角

  static double vectorAngle(const Point2d & vecA, const Point2d & vecB)
  {
	  return  vectorProduct(vecA, vecB) / vectorBig(vecA) / vectorBig(vecB);
  
  }

  //求向量夹角最小值

 /* void MinAngle(const vector<Point2d> & vecA, vector<Point2d> & vecB)
  {
	 
	 vector<Point2d> tempvector;
	
		
		 for (auto i = vecA.begin(); i != vecA.end(); ++i)

		 {
			  double Min = 1;
			  Point2d MinPoint;
			  for (auto j = vecB.begin(); j != vecB.end(); ++j)
			  {
				 if (vectorAngle(*i, *j) <=Min)
				 {
					 Min = vectorAngle(*i, *j);
					 MinPoint = *j;
				 }
			  }
			 tempvector.push_back(MinPoint);
		 }

	 vecB = tempvector;
  
  }*/

 vector<Point2d> MinAngle(const vector<pair<Point2d, Point2d>> & lessvector, const vector<pair<Point2d, Point2d>>& moreVector)
  {

	  vector<Point2d> tempvector;
	  for (auto i = lessvector.begin(); i != lessvector.end(); ++i)

	  {
		  double Min = 0;
		  Point2d MinPoint;
		  for (auto j = moreVector.begin(); j != moreVector.end(); ++j)
		  {
			  double  tempDou = vectorAngle((*i).second, (*j).second);
			  if (tempDou >= Min && tempDou>=0)
			  {
				  Min = tempDou;
				  MinPoint = (*j).first;
			  }
		  }
		  tempvector.push_back(MinPoint);
	  }

	  return  tempvector;

  }


 void Registor(vector<Point2d> & lessVec, vector<Point2d> & moreVec)
 {
	 vector<Point2d>  divideGroup1;
	 vector<Point2d>  divideGroup2;

	 if (DivGroup(lessVec, divideGroup1) && DivGroup(moreVec, divideGroup2))
	 {
		 //cout << "wrong in register" << endl;
	 }

	 vector<pair<Point2d, Point2d>> dvector1;
	 vector<pair<Point2d, Point2d>>  dvector2;

	 dvector1 = Dovector(divideGroup1);
	 dvector2 = Dovector(divideGroup2);
	 lessVec = divideGroup1;
	 moreVec = MinAngle(dvector1, dvector2);

	/* for (auto i = lessVec.begin(); i != lessVec.end(); ++i)
	 {
		 cout << (*i) << endl;
	 }

	 for (auto i = moreVec.begin(); i != moreVec.end(); ++i)
	 {
	 cout << (*i)<< endl;
	 }*/

 }

//void main()
//{
//	//vector<Point2d> a{ Point2d(831, 360), Point2d(976, 497), Point2d(735, 498), Point2d(830, 657) };
//	vector<Point2d> a{  Point2d(976, 497), Point2d(735, 498), Point2d(830, 657) };
//	//vector<Point2d> a{ Point2d(831, 360), Point2d(976, 497), Point2d(735, 498)};
//    vector<Point2d> b{ Point2d(466, 381), Point2d(368, 517), Point2d(613, 519), Point2d(462, 677) };
// //   vector<Point2d> b{ Point2d(466, 381), Point2d(368, 517), Point2d(613, 519) };
//
//	Registor(a, b);
//	system("pause");
//}
