
#include<iostream>
#include <fstream> 
#include <iterator>  
#include <vector> 

#include "MarksConstruction.h"
#include "GetImage.h"
#include  "ThreeDimPoint.h"  
using namespace cv;
using namespace std;


//�����������������matlab����
//const string LEFT_FILE_NAME = "HL.xml";//ע������ط���ôд
//const string  RIGHT_FILE_NAME = "HR.xml";
static Mat ML(3, 4, CV_64FC1);
static Mat MR(3, 4, CV_64FC1);


//�������������ʹ�õı���
static Mat K(4, 3, CV_64FC1);//kX=l
static Mat L(4, 1, CV_64FC1);
//�����м����������Ϊȫ�֣�����������ͷŵ�ʱ������
static Mat m34(3, 4, CV_64FC1);
static Mat m33(3, 3, CV_64FC1);
static Mat m31(3, 1, CV_64FC1);
static  Mat cameraMatrixR(3, 3, CV_32FC1);
/*
* ��ʼ�����
* �궨�������������
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
	//��ʼ����ȡͼ������豸
	InitGetImages();


	//��ʼ������궨�ڲκ����
	WriteDate();

}


/*
* ����ռ�λ��
* plx: ���������X����
* ply�����������Y����
* prx�����������X����
* pry�����������Y����
* out3D��double [3] ���飬��ʾ�ռ�����x��y��z�����������������궨ԭ�㡣
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
	out3d.x = m31.at<double>(0, 0);//���ܶԿ�ָ����в���
	out3d.y = m31.at<double>(1, 0);
	out3d.z = m31.at<double>(2, 0);

	cout << "��ά�ؽ����"<<out3d.x << "  " << out3d.y << "  " << out3d.z<<endl;
	return true;
}



//��Ϣ��ʧ����£���ά�ؽ�
void restructMarks(vector<Point3d>&marks3d)//��Ҫ�Ǹ��ṹ�帳ֵ
{

	
		Point3d miss;
		for (auto i = marks3d.begin(); i != marks3d.end(); i++)
			cout << "ֻ�ؽ�������" << *i << endl;

		miss = OtherThree(marks3d[0], marks3d[1], marks3d[2]);

		marks3d.push_back(miss);


}

