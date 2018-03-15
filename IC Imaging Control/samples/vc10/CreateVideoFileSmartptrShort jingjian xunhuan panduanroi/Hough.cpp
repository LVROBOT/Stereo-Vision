#include"Hough.h"



IplImage* leftdst = cvCreateImage(cvSize(1280,960), IPL_DEPTH_8U, 1);
IplImage* rightdst = cvCreateImage(cvSize(1280,960), IPL_DEPTH_8U, 1);


CvSeq* circlesleft = NULL;
CvSeq* circlesright = NULL;

//int   cirtotalleft = circlesleft->total;
//int   cirtotalright = circlesright->total;
//
//vector<CvPoint> prankLeft(cirtotalleft);
//vector<CvPoint> prankRight(cirtotalright);

vector<CvPoint> prankLeft;
vector<CvPoint> prankRight;

void SWAP(CvPoint &x, CvPoint &y)//交换
{

	CvPoint t;
	t = x, x = y, y = t;
};

void sort(vector<CvPoint> &vecTest, int n)//选择排序
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


	//cvAdaptiveThreshold(src, dst, 200, CV_ADAPTIVE_THRESH_MEAN_C, CV_THRESH_BINARY, 3, 5);////自适应阈值

	cvAdaptiveThreshold(src, dst, 200, CV_ADAPTIVE_THRESH_GAUSSIAN_C, CV_THRESH_BINARY, 17, 15);////自适应阈值

	cvSmooth(dst, dst, CV_GAUSSIAN, 3, 3);
	(dst, dst, CV_MEDIAN, 3, 3);
	cvErode(dst, dst, 0, 1);
	cvDilate(dst, dst, 0, 1);
	cvErode(dst, dst, 0, 1);
	cvDilate(dst, dst, 0, 1);
	cvErode(dst, dst, 0, 1);
	cvDilate(dst, dst, 0, 1);
	cvErode(dst, dst, 0, 1);
};

 
void Bismooth(MemBufferCollection::tMemBufferPtr& Pleft, MemBufferCollection::tMemBufferPtr & Pright)
{
	IplImage* leftRGB = cvCreateImage(cvSize(1280, 960), IPL_DEPTH_8U, 3);//是三通道的
	IplImage* rightRGB = cvCreateImage(cvSize(1280, 960), IPL_DEPTH_8U, 3);//////////////////

	IplImage* leftImage = cvCreateImage(cvSize(1280, 960), IPL_DEPTH_8U, 1);
	IplImage* rightImage = cvCreateImage(cvSize(1280, 960), IPL_DEPTH_8U, 1);


	leftRGB->imageData = (char*)(Pleft->getPtr());//内部缓存区的指针，返回_UDSHL_EXP_API BYTE*	
	rightRGB->imageData = (char*)(Pright->getPtr());/////////////

	cvCvtColor(leftRGB, leftImage, CV_RGB2GRAY);/////////////////通道个数存在问题
	cvCvtColor(rightRGB, rightImage, CV_RGB2GRAY);////////////////

	IplImage* leftImagef = cvCreateImage(cvSize(1280, 960), IPL_DEPTH_8U, 1);
	IplImage* rightImagef = cvCreateImage(cvSize(1280, 960), IPL_DEPTH_8U, 1); 

	cvFlip(leftImage, leftImagef,1);
	//cvFlip(leftImage);

	cvFlip(rightImage, rightImagef,1);
	//cvFlip(rightImage);

	Smooth(leftImagef, leftdst);
	Smooth(rightImagef, rightdst);


	//MyROI(leftdst, prankLeft);

	// MyROI(rightdst, prankRight);
};


 int ROIx = 0;
 int ROIy = 0;
void MyROI(IplImage* dst, vector<CvPoint> &vecTest)
{
     

	int widthROI =1280;
	int  heightROI =960;

	int x1 = vecTest[0].x-10;
	int y1 = vecTest[0].y-10;

	if ((heightROI + ROIy <960) && (widthROI + ROIx < 1280))
	
			
		//if ((0 < x1)  && (0 < y1) )
			{
				ROIx = x1;
				widthROI = 350;

				ROIy = y1;
				heightROI = 330;

			}
			
	
	else
	{
		int ROIx = 0;
		int ROIy = 0;

		int widthROI = 1280;
		int  heightROI = 960;

	}

	cout << ROIx << ROIy << endl;

	cvSetImageROI(dst, cvRect(ROIx, ROIy, widthROI, heightROI));


}


void SaveCircles(const char *Filename, vector<CvPoint>  &vecTest)
{
		ofstream write;
		write.open(Filename, ofstream::app);//模式为输出和追加
		for (int i = 0; i < 4; i++)
			write << vecTest[i].x + ROIx<< "   " << vecTest[i].y + ROIy<< endl;
		write.close();
}

void ExCircles(CvArr* dstleft, CvArr* dstright)
{

	CvMemStorage* storageleft = cvCreateMemStorage(0);
	CvMemStorage* storageright = cvCreateMemStorage(0);

	CvSeq* circlesleft = cvHoughCircles(dstleft, storageleft, CV_HOUGH_GRADIENT, 1, 60, 100, 15, 15, 20);
	CvSeq* circlesright = cvHoughCircles(dstright, storageright, CV_HOUGH_GRADIENT, 1, 60, 100, 15, 15, 20);


	IplImage* colorLeft = cvCreateImage(cvGetSize(dstleft), IPL_DEPTH_8U, 3);
	cvCvtColor(dstleft, colorLeft, CV_GRAY2RGB);

	IplImage* colorRight = cvCreateImage(cvGetSize(dstright), IPL_DEPTH_8U, 3);
	cvCvtColor(dstright, colorRight, CV_GRAY2RGB);


	for (int i = 0; i < circlesleft->total; i++)
	{
		float* p = (float*)cvGetSeqElem(circlesleft, i);
		CvPoint pt = cvPoint(cvRound(p[0]), cvRound(p[1]));
		prankLeft.push_back(pt);

		cvCircle(colorLeft, pt, cvRound(p[2]), CV_RGB(255, 0, 0), 1, 8, 0);
		cvNamedWindow("Left", 1);
		cvShowImage("Left", colorLeft);

	}




	for (int i = 0; i < circlesright->total; i++)
	{
		float* p = (float*)cvGetSeqElem(circlesright, i);
		CvPoint pt = cvPoint(cvRound(p[0]), cvRound(p[1]));
		prankRight.push_back(pt);


		cvCircle(colorRight, pt, cvRound(p[2]), CV_RGB(255, 0, 0), 1, 8, 0);
		cvNamedWindow("Right", 1);
		cvShowImage("Right", colorRight);

	}


	sort(prankLeft, circlesleft->total);

	sort(prankRight, circlesright->total);

	if ((4 == (circlesleft->total)) && (4 == (circlesright->total)))

	{
		cout << "右边图像" << endl;

		for (int i = 0; i < 4; i++)
		{
			cout << prankRight[i].x << "   " << prankRight[i].y << endl;
		}

		cout << "左边图像" << endl;

		for (int i = 0; i < 4; i++)
		{
			cout << prankLeft[i].x << "   " << prankLeft[i].y << endl;
		}



		SaveCircles("left.txt", prankLeft);

		SaveCircles("right.txt", prankRight);

	}


}