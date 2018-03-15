#include"Hough.h"


CvMemStorage* storageLeft = cvCreateMemStorage(0);
CvMemStorage* storageRight = cvCreateMemStorage(0);

IplImage* leftRGB = cvCreateImage(cvSize(1280, 960), IPL_DEPTH_8U, 3);//����ͨ����
IplImage* rightRGB = cvCreateImage(cvSize(1280, 960), IPL_DEPTH_8U, 3);//////////////////

IplImage* leftImage = cvCreateImage(cvSize(1280, 960), IPL_DEPTH_8U, 1);
IplImage* rightImage = cvCreateImage(cvSize(1280, 960), IPL_DEPTH_8U, 1);

IplImage* leftdst = cvCreateImage(cvSize(1280, 960), IPL_DEPTH_8U, 1);
IplImage* rightdst = cvCreateImage(cvSize(1280, 960), IPL_DEPTH_8U, 1);

void SWAP(CvPoint &x, CvPoint &y)//����
{

	CvPoint t;
	t = x, x = y, y = t;
};

void sort(vector<CvPoint> &vecTest, int n)//ѡ������
{
	int i, j, min;
	for (i = 0; i < n - 1; i++){
		min = i;
		for (j = i + 1; j < n; j++)
			if (vecTest[j].x < vecTest[min].x || ((vecTest[j].x == vecTest[min].x) && vecTest[j].y < vecTest[min].y))

				//if (vecTest[j].x < vecTest[min].x )
				min = j;


		SWAP(vecTest[i], vecTest[min]);
	}
};

void Bismooth(const CvArr* src, CvArr* dst)
{
	cvAdaptiveThreshold(src, dst, 200, CV_ADAPTIVE_THRESH_GAUSSIAN_C, CV_THRESH_BINARY, 17, 15);////����Ӧ��ֵ
	cvSmooth(dst, dst, CV_GAUSSIAN, 3, 3);
	cvErode(dst, dst, 0, 1);
	cvDilate(dst, dst, 0, 1);
	cvErode(dst, dst, 0, 1);
	cvDilate(dst, dst, 0, 1);
	cvErode(dst, dst, 0, 1);
	cvDilate(dst, dst, 0, 1);
	cvErode(dst, dst, 0, 1);

};

void DrawCircles(CvArr* dst, CvSeq* circles,const char *Filename)

{
	IplImage* color = cvCreateImage(cvSize(1280, 960), IPL_DEPTH_8U, 3);
	cvCvtColor(dst, color, CV_GRAY2RGB);//ת������ͨ��

	int Cir_total = circles->total;//////////////////���Է�������

     vector<CvPoint> prank(Cir_total);//�������� ��С��һ��////����


	 ///////////////////////////////
	for (int i = 0; i < Cir_total; i++)
	{
		float* p = (float*)cvGetSeqElem(circles, i);
		CvPoint pt = cvPoint(cvRound(p[0]), cvRound(p[1]));
		prank[i] = pt;
		
			//cout << "Բ������x= " << cvRound(p[0]) << endl << "Բ������y= " << cvRound(p[1]) << endl;
			//cout << "�뾶=" << cvRound(p[2]) << endl;
			cvCircle(color, pt, cvRound(p[2]), CV_RGB(255, 0, 0), 1, 8, 0);
			cvNamedWindow("co", 1);
			cvShowImage("co", color);
		

	}
	//////////////////////////////////////////////////////����

	sort(prank, Cir_total);
	for (int i = 0; i < Cir_total; i++)
		cout << prank[i].x << "   " << prank[i].y << endl;

	//////////////////////////////////////////////////////����Ϊtxt�ļ�
	ofstream write;
	write.open(Filename);
	for (int i = 0; i < Cir_total; i++)
		write << prank[i].x << "   " << prank[i].y << endl;
	write.close();

};

 