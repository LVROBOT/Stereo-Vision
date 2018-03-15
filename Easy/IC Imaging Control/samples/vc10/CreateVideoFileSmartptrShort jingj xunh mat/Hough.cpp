#include"Hough.h"



Mat  leftdst ;//�޸�
Mat  rightdst ;//�޸�

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

void Smooth(const Mat & src, Mat dst)

{


	//cvAdaptiveThreshold(src, dst, 200, CV_ADAPTIVE_THRESH_MEAN_C, CV_THRESH_BINARY, 3, 5);////����Ӧ��ֵ

	adaptiveThreshold(src, dst, 200, CV_ADAPTIVE_THRESH_GAUSSIAN_C, CV_THRESH_BINARY, 17, 15);////����Ӧ��ֵ

	GaussianBlur(dst, dst, Size(3,3), 2, 2);
	erode(dst, dst, 0);
	dilate(dst, dst, 0);
	erode(dst, dst, 0);
	dilate(dst, dst, 0);
	erode(dst, dst, 0);
	dilate(dst, dst, 0);
	erode(dst, dst, 0);

};

 
void Bismooth(MemBufferCollection::tMemBufferPtr& Pleft, MemBufferCollection::tMemBufferPtr & Pright)
{
	Mat leftRGB(1280, 960, IPL_DEPTH_8U, 3);//����ͨ����//�޸�
	Mat rightRGB(1280, 960, IPL_DEPTH_8U, 3);////////////////////�޸�

	Mat leftImage(1280, 960, IPL_DEPTH_8U, 1);//�޸�
	Mat rightImage(1280, 960, IPL_DEPTH_8U, 1);//�޸�


	leftRGB.data = (uchar*)(Pleft->getPtr());//�ڲ���������ָ�룬����_UDSHL_EXP_API BYTE*	
	rightRGB.data = (uchar*)(Pright->getPtr());/////////////

	cvtColor(leftRGB, leftImage, CV_RGB2GRAY);/////////////////ͨ��������������
	cvtColor(rightRGB, rightImage, CV_RGB2GRAY);////////////////

	//IplImage* leftImagef = cvCreateImage(cvSize(1280, 960), IPL_DEPTH_8U, 1);
	//IplImage* rightImagef = cvCreateImage(cvSize(1280, 960), IPL_DEPTH_8U, 1); 

	//flip(leftImage, leftImagef,1);
	//cvFlip(leftImage);

	//cvFlip(rightImage, rightImagef,1);
	//cvFlip(rightImage);

	Smooth(leftImage, leftdst);
	Smooth(rightImage, rightdst);

	
};


void ExCircles(Mat &dst, const char *Filename)

{
	Mat circles;
	HoughCircles(dst, circles, CV_HOUGH_GRADIENT, 1, 80, 150, 15, 15, 20);

	Mat color;//////////////////////////////////////////////////////////�޸�
	cvtColor(dst, color, CV_GRAY2RGB);//ת������ͨ��
	
		//auto Cir_total = circles.total;//////////////////���Է�������
	//	cout << Filename << " " << Cir_total<<endl;//�����õ�
	    // vector<CvPoint> prank(Cir_total);//�������� ��С��һ��////����


		 cout << circles << endl;
	
	
		// /////������  ������ȡ��Բ
		// for ( i = 0; i < Cir_total; i++)
		//{
		//	Point pt = circles();
		//	prank[i] = pt;
		//	
		//		//cout << "Բ������x= " << cvRound(p[0]) << endl << "Բ������y= " << cvRound(p[1]) << endl;
		//		//cout << "�뾶=" << cvRound(p[2]) << endl;
		//		circle(color, pt, cvRound(p[2]), CV_RGB(255, 0, 0), 1, 8, 0);
		//		namedWindow(Filename, 0);
		//		imshow(Filename, color);

		//		
		//	
	
		//}
		//////////////////////////////////////////////////////����
	
		//sort(prank, Cir_total);
		//for (int i = 0; i < Cir_total; i++)
		//	cout << prank[i].x << "   " << prank[i].y << endl;// �������Ч��
	
		////////////////////////////////////////////////////////����Ϊtxt�ļ�
		//ofstream write;
		//write.open(Filename,ofstream::app);//ģʽΪ�����׷��
		//for (int i = 0; i < Cir_total; i++)
		//	write << prank[i].x << "   " << prank[i].y << endl;
		//write.close();


}

