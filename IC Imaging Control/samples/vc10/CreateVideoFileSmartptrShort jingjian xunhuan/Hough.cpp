#include"Hough.h"

IplImage* leftdst = cvCreateImage(cvSize(1280,960), IPL_DEPTH_8U, 1);
IplImage* rightdst = cvCreateImage(cvSize(1280,960), IPL_DEPTH_8U, 1);

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

void Smooth(const CvArr* src, CvArr* dst)

{

	//cvAdaptiveThreshold(src, dst, 200, CV_ADAPTIVE_THRESH_MEAN_C, CV_THRESH_BINARY, 3, 5);////����Ӧ��ֵ

	cvAdaptiveThreshold(src, dst, 200, CV_ADAPTIVE_THRESH_GAUSSIAN_C, CV_THRESH_BINARY, 17, 15);////����Ӧ��ֵ

	cvSmooth(dst, dst, CV_GAUSSIAN, 3, 3);

	cvErode(dst, dst, 0, 1);

	cvDilate(dst, dst, 0, 1);

	cvErode(dst, dst, 0, 1);

	cvDilate(dst, dst, 0, 1);

	cvErode(dst, dst, 0, 1);

	/*cvDilate(dst, dst, 0, 1);

	cvErode(dst, dst, 0, 1);*/

};

//void Smooth( CvArr* src, CvArr* dst)//   ����Ӧ��ֵ�Ͷ�ֵ���ĸ���
//
//{
//
//	//cvAdaptiveThreshold(src, dst, 200, CV_ADAPTIVE_THRESH_MEAN_C, CV_THRESH_BINARY, 3, 5);////����Ӧ��ֵ
//
//	
//
//	cvSmooth(src,src, CV_GAUSSIAN,5, 5,0,0);
//
//	cvErode(src, src, 0, 1);
//
//	cvDilate(src, src, 0, 1);
//
//	/*cvErode(src, src, 0, 1);
//
//	cvDilate(src, src, 0, 1);
//
//	cvErode(src, src, 0, 1);
//
//	cvDilate(dst, dst, 0, 1);
//
//	cvErode(dst, dst, 0, 1);*/
////cvAdaptiveThreshold(src, dst, 200, CV_ADAPTIVE_THRESH_GAUSSIAN_C, CV_THRESH_BINARY, 17, 15);////����Ӧ��ֵ
//  cvCanny(src, dst, 80, 40, 3);
//};
 
void Bismooth(MemBufferCollection::tMemBufferPtr& Pleft, MemBufferCollection::tMemBufferPtr & Pright)
{
	IplImage* leftRGB = cvCreateImage(cvSize(1280, 960), IPL_DEPTH_8U, 3);//����ͨ����
	IplImage* rightRGB = cvCreateImage(cvSize(1280, 960), IPL_DEPTH_8U, 3);//////////////////

	IplImage* leftImage = cvCreateImage(cvSize(1280, 960), IPL_DEPTH_8U, 1);
	IplImage* rightImage = cvCreateImage(cvSize(1280, 960), IPL_DEPTH_8U, 1);


	leftRGB->imageData = (char*)(Pleft->getPtr());//�ڲ���������ָ�룬����_UDSHL_EXP_API BYTE*	
	rightRGB->imageData = (char*)(Pright->getPtr());/////////////

	cvCvtColor(leftRGB, leftImage, CV_RGB2GRAY);/////////////////ͨ��������������
	cvCvtColor(rightRGB, rightImage, CV_RGB2GRAY);////////////////

	IplImage* leftImagef = cvCreateImage(cvSize(1280, 960), IPL_DEPTH_8U, 1);
	IplImage* rightImagef = cvCreateImage(cvSize(1280, 960), IPL_DEPTH_8U, 1); 

	cvFlip(leftImage, leftImagef,1);
	//cvFlip(leftImage);

	cvFlip(rightImage, rightImagef,1);
	//cvFlip(rightImage);

	//Smooth(leftImagef, leftdst);
	//Smooth(rightImagef, rightdst);

	leftdst = leftImagef;
	rightdst = rightImagef;

	
};

void ExCircles(CvArr* dst, const char *Filename)

{
	CvMemStorage* storage = cvCreateMemStorage(0);

	CvSeq* circles = cvHoughCircles(dst, storage, CV_HOUGH_GRADIENT, 1, 80,200,25,15,35);//30�޸��˲���

	//CvSeq* circles = cvHoughCircles(dst, storage, CV_HOUGH_GRADIENT, 1, 80, 150, 15, 25, 30);//̧��

	IplImage* color = cvCreateImage(cvSize(1280,960), IPL_DEPTH_8U, 3);////////////////////////////////////////////////////////
		cvCvtColor(dst, color, CV_GRAY2RGB);//ת������ͨ��
	
		int Cir_total = circles->total;//////////////////���Է�������

			cout << Filename << " " << Cir_total << endl;
		//	vector<CvPoint> prank(Cir_total);//�������� ��С��һ��////����

			vector<CvPoint> prank;

			/////������  ������ȡ��Բ
			for (int i = 0; i < Cir_total; i++)
			{
				float* p = (float*)cvGetSeqElem(circles, i);
				CvPoint pt = cvPoint(cvRound(p[0]), cvRound(p[1]));
				//prank[i] = pt;

				prank.push_back(pt);

				//cout << "Բ������x= " << cvRound(p[0]) << endl << "Բ������y= " << cvRound(p[1]) << endl;
				//cout << "�뾶=" << cvRound(p[2]) << endl;
				cvCircle(color, pt, cvRound(p[2]), CV_RGB(255, 0, 0), 1, 8, 0);
				cvNamedWindow(Filename, 0);
				cvShowImage(Filename, color);

			}
			//////////////////////////////////////////////////////����

			sort(prank, Cir_total);
			for (int i = 0; i < Cir_total; i++)
				cout << prank[i].x << "   " << prank[i].y << endl;// �������Ч��

			//////////////////////////////////////////////////////����Ϊtxt�ļ�
			ofstream write;
			write.open(Filename, ofstream::app);//ģʽΪ�����׷��
			for (int i = 0; i < Cir_total; i++)
				write << prank[i].x << "   " << prank[i].y << endl;
			write.close();

}

