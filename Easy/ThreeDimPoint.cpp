#include <iostream>
#include <math.h>
#include <algorithm>  
#include <utility>  //定义pair 类型
#include  "ThreeDimPoint.h"  
using namespace cv;
using namespace std;

//输出三维点
void print(const Point3d &p)
{
	cout << "(" << p.x << "," << p.y << "," << p.z << ")" << endl;
}

//两点间的距离
double pointDistance(Point3d p1, Point3d p2)
{
	double distance = 0;
	distance = sqrt((p1.y - p2.y)*(p1.y - p2.y) + (p1.x - p2.x)*(p1.x - p2.x) + (p1.z - p2.z)*(p1.z - p2.z));
	return distance;
}

//已知三角形的三点坐标，求面积
double area(Point3d p1, Point3d p2, Point3d p3)
{
	double area = 0;
	double a = 0, b = 0, c = 0, s = 0;
	a = pointDistance(p1, p2);
	b = pointDistance(p2, p3);
	c = pointDistance(p1, p3);
	s = 0.5*(a + b + c);
	area = sqrt(s*(s - a)*(s - b)*(s - c));
	return area;
}

//三点间的角度
vector<double>  pointAngle(Point3d p1, Point3d p2, Point3d p3)
{
	double a = 0, b = 0, c = 0;
	a = pointDistance(p1, p2);
	b = pointDistance(p2, p3);
	c = pointDistance(p1, p3);

	vector<double> angle;
	double Cos_c = (a*a + b*b - c*c) / (2 * a*b);
	double angle_c = acos(Cos_c) * 180 / 3.14;
	angle.push_back(angle_c);

	double Cos_b = (a*a - b*b + c*c) / (2 * a*c);
	double angle_b = acos(Cos_b) * 180 / 3.14;
	angle.push_back(angle_b);

	double Cos_a = ((-a*a) + b*b + c*c) / (2 * b*c);
	double angle_a = acos(Cos_a) * 180 / 3.14;
	angle.push_back(angle_a);

	return angle;
}

//寻找三角形的最长边
double LongDis(Point3d p1, Point3d p2, Point3d p3)//找最长的边
{
	double a = 0, b = 0, c = 0;
	vector<double> Distance;

	a = pointDistance(p1, p2);
	Distance.push_back(a);

	b = pointDistance(p2, p3);
	Distance.push_back(b);

	c = pointDistance(p1, p3);
	Distance.push_back(c);
	sort(Distance.begin(), Distance.end());

	return Distance[2];
}

//确定那个点丢失了
string MissFind(Point3d p1, Point3d p2, Point3d p3)
{

	vector<double>  distancelong{ 88, 72.91 };
	vector<double>  FourArea7{ 1720.86, 1487.14 };//长边为72的面积
	vector<double>  FourArea8{ 1949.89, 1258.12 };//长边为88的面积


	double area1 = 0, LongDis1 = 0;
	LongDis1 = LongDis(p1, p2, p3);//求最长边
	area1 = area(p1, p2, p3);//求面积

	vector<double>  NearDis;

	NearDis.push_back(abs(distancelong[0] - LongDis1));
	NearDis.push_back(abs(distancelong[1] - LongDis1));

	if (NearDis[0] > NearDis[1])//最长边为72.91缺AC
	{
		vector<double>  NearArea1;
		NearArea1.push_back(abs(FourArea7[0] - area1));
		NearArea1.push_back(abs(FourArea7[1] - area1));
		if (NearArea1[0] > NearArea1[1])
		{
			return "C";
		}

		return "A";

	}

	else
	{
		vector<double>  NearArea2;
		NearArea2.push_back(abs(FourArea8[0] - area1));
		NearArea2.push_back(abs(FourArea8[1] - area1));
		if (NearArea2[0] > NearArea2[1])
		{

			return "D";
		}

		return "B";

	}


}

//三点的名字
vector<Point3d> PointName(Point3d p1, Point3d p2, Point3d p3)
{

	double a = 0, b = 0, c = 0;
	vector<pair<double, Point3d>> disPoint;

	a = pointDistance(p1, p2);
	pair<double, Point3d> DP1{ a, p3 };
	disPoint.push_back(DP1);

	b = pointDistance(p2, p3);
	pair<double, Point3d> DP2{ b, p1 };
	disPoint.push_back(DP2);

	c = pointDistance(p1, p3);
	pair<double, Point3d> DP3{ c, p2 };
	disPoint.push_back(DP3);


	sort(disPoint.begin(), disPoint.end(), [](const pair<double, Point3d> &a, const pair<double, Point3d>&b){return a.first >b.first; });

	vector<Point3d> threepoint;

	threepoint.push_back(disPoint[0].second);
	threepoint.push_back(disPoint[1].second);
	threepoint.push_back(disPoint[2].second);

	return threepoint;
}


//向量大小带平方
double  Big(Point3d p)
{
	double a1 = (p.x*p.x + p.y*p.y + p.z*p.z);
	return a1;

}

//已知三点求平面

vector <double> get_panel(Point3d p1, Point3d p2, Point3d p3)

{
	double a = 0;
	double b = 0;
	double c = 0;
	double d = 0;

	vector <double>  W;

	a = ((p2.y - p1.y)*(p3.z - p1.z) - (p2.z - p1.z)*(p3.y - p1.y));
	//	W.push_back(a);
	b = ((p2.z - p1.z)*(p3.x - p1.x) - (p2.x - p1.x)*(p3.z - p1.z));
	//	W.push_back(b);
	c = ((p2.x - p1.x)*(p3.y - p1.y) - (p2.y - p1.y)*(p3.x - p1.x));
	//	W.push_back(c);
	d = (0 - (a*p1.x + b*p1.y + c*p1.z));
	//	W.push_back(d);

	//cout << a<< " " << b << " " << c<< " " << d << endl;

	W.push_back(a / d);

	W.push_back(b / d);

	W.push_back(c / d);
	W.push_back(1);

	return  W;

}


//已知三点是哪三个点，求另一个点
Point3d  OtherThree(Point3d p1, Point3d p2, Point3d p3)

{
	string Miss = MissFind(p1, p2, p3);

	cout << "丢失的点" << Miss << endl;
	vector<Point3d> Others;
	Others = PointName(p1, p2, p3);//确定三点各自是谁 v1v2v3知道了

	cout << "others" << endl;
	for (auto i = Others.begin(); i != Others.end(); ++i)
		cout << *i << endl;


	vector<double> panel;
	panel = get_panel(p1, p2, p3);//平面系数

	cout << "panel" << endl;
	for (auto i = panel.begin(); i != panel.end(); ++i)
		cout << *i << endl;



	if (Miss == "A")
	{

		vector<double> Constdis{ 88, 50, 60 };

		//矩阵初始化
		double m[9] = { 2 * (Others[1].x - Others[0].x), 2 * (Others[1].y - Others[0].y), 2 * (Others[1].z - Others[0].z),
			2 * (Others[2].x - Others[1].x), 2 * (Others[2].y - Others[1].y), 2 * (Others[2].z - Others[1].z),
			panel[0], panel[1], panel[2] };

		double mb[3] = { Big(Others[1]) - Big(Others[0]) - Constdis[1] * Constdis[1] + Constdis[0] * Constdis[0],
			Big(Others[2]) - Big(Others[1]) - Constdis[2] * Constdis[2] + Constdis[1] * Constdis[1], -1 };

		CvMat *Ma = cvCreateMat(3, 3, CV_64FC1); //左边的坐标矩阵    
		cvSetData(Ma, m, CV_AUTOSTEP);

		CvMat *Mb = cvCreateMat(3, 1, CV_64FC1); //右边的坐标矩阵    
		cvSetData(Mb, mb, CV_AUTOSTEP);

		CvMat *Mx = cvCreateMat(3, 1, CV_64FC1); //要求解的矩阵   

		cvSolve(Ma, Mb, Mx, CV_LU); // solve (Ax=b) for x   

		Point3d  fourpoint;

		fourpoint = Point3d(Mx->data.db[0], (Mx->data.db[1]), (Mx->data.db[2]));


		cvReleaseMat(&Ma);
		cvReleaseMat(&Mb);
		cvReleaseMat(&Mx);
		return fourpoint;

	}

	if (Miss == "B")
	{

		vector<double> Constdis{ 72.91, 50, 55 };

		//矩阵初始化
		double m[9] = { 2 * (Others[1].x - Others[0].x), 2 * (Others[1].y - Others[0].y), 2 * (Others[1].z - Others[0].z),
			2 * (Others[2].x - Others[1].x), 2 * (Others[2].y - Others[1].y), 2 * (Others[2].z - Others[1].z),
			panel[0], panel[1], panel[2] };

		double mb[3] = { Big(Others[1]) - Big(Others[0]) - Constdis[1] * Constdis[1] + Constdis[0] * Constdis[0],
			Big(Others[2]) - Big(Others[1]) - Constdis[2] * Constdis[2] + Constdis[1] * Constdis[1], -1 };

		CvMat *Ma = cvCreateMat(3, 3, CV_64FC1); //左边的坐标矩阵    
		cvSetData(Ma, m, CV_AUTOSTEP);

		CvMat *Mb = cvCreateMat(3, 1, CV_64FC1); //右边的坐标矩阵    
		cvSetData(Mb, mb, CV_AUTOSTEP);

		CvMat *Mx = cvCreateMat(3, 1, CV_64FC1); //要求解的矩阵   

		cvSolve(Ma, Mb, Mx, CV_LU); // solve (Ax=b) for x   

		Point3d  fourpoint;

		fourpoint = Point3d(Mx->data.db[0], (Mx->data.db[1]), (Mx->data.db[2]));

		cvReleaseMat(&Ma);
		cvReleaseMat(&Mb);
		cvReleaseMat(&Mx);
		return fourpoint;


	}

	if (Miss == "C")
	{

		vector<double> Constdis{ 88, 55, 65 };

		//矩阵初始化
		double m[9] = { 2 * (Others[1].x - Others[0].x), 2 * (Others[1].y - Others[0].y), 2 * (Others[1].z - Others[0].z),
			2 * (Others[2].x - Others[1].x), 2 * (Others[2].y - Others[1].y), 2 * (Others[2].z - Others[1].z),
			panel[0], panel[1], panel[2] };

		double mb[3] = { Big(Others[1]) - Big(Others[0]) - Constdis[1] * Constdis[1] + Constdis[0] * Constdis[0],
			Big(Others[2]) - Big(Others[1]) - Constdis[2] * Constdis[2] + Constdis[1] * Constdis[1], -1 };

		CvMat *Ma = cvCreateMat(3, 3, CV_64FC1); //左边的坐标矩阵    
		cvSetData(Ma, m, CV_AUTOSTEP);

		CvMat *Mb = cvCreateMat(3, 1, CV_64FC1); //右边的坐标矩阵    
		cvSetData(Mb, mb, CV_AUTOSTEP);

		CvMat *Mx = cvCreateMat(3, 1, CV_64FC1); //要求解的矩阵   

		cvSolve(Ma, Mb, Mx, CV_LU); // solve (Ax=b) for x   

		Point3d  fourpoint;

		fourpoint = Point3d(Mx->data.db[0], (Mx->data.db[1]), (Mx->data.db[2]));

		cvReleaseMat(&Ma);
		cvReleaseMat(&Mb);
		cvReleaseMat(&Mx);
		return fourpoint;


	}

	if (Miss == "D")
	{

		vector<double> Constdis{ 72.91, 60, 65 };

		//矩阵初始化
		double m[9] = { 2 * (Others[1].x - Others[0].x), 2 * (Others[1].y - Others[0].y), 2 * (Others[1].z - Others[0].z),
			2 * (Others[2].x - Others[1].x), 2 * (Others[2].y - Others[1].y), 2 * (Others[2].z - Others[1].z),
			panel[0], panel[1], panel[2] };

		double mb[3] = { Big(Others[1]) - Big(Others[0]) - Constdis[1] * Constdis[1] + Constdis[0] * Constdis[0],
			Big(Others[2]) - Big(Others[1]) - Constdis[2] * Constdis[2] + Constdis[1] * Constdis[1], -1 };

		CvMat *Ma = cvCreateMat(3, 3, CV_64FC1); //左边的坐标矩阵    
		cvSetData(Ma, m, CV_AUTOSTEP);

		CvMat *Mb = cvCreateMat(3, 1, CV_64FC1); //右边的坐标矩阵    
		cvSetData(Mb, mb, CV_AUTOSTEP);

		CvMat *Mx = cvCreateMat(3, 1, CV_64FC1); //要求解的矩阵   

		cvSolve(Ma, Mb, Mx, CV_LU); // solve (Ax=b) for x   

		Point3d  fourpoint;

		fourpoint = Point3d(Mx->data.db[0], (Mx->data.db[1]), (Mx->data.db[2]));

		cvReleaseMat(&Ma);
		cvReleaseMat(&Mb);
		cvReleaseMat(&Mx);
		return fourpoint;

	}

}


