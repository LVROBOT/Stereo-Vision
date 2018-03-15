#include"Hough.h"



IplImage* leftdst = cvCreateImage(cvSize(1280,960), IPL_DEPTH_8U, 1);
IplImage* rightdst = cvCreateImage(cvSize(1280,960), IPL_DEPTH_8U, 1);


CvSeq* circlesleft = NULL;
CvSeq* circlesright = NULL;

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

	
};


void SaveCircles(CvArr* dst, const char *Filename, CvSeq* circles)
{

	IplImage* color = cvCreateImage(cvSize(1280, 960), IPL_DEPTH_8U, 3);////////////////////////////////////////////////////////等一下
	cvCvtColor(dst, color, CV_GRAY2RGB);//转化成三通道  等一下


		cout << Filename << " " << 4<< endl;
		vector<CvPoint> prank(4);//定义向量 大小不一定////可以


		/////调试用  画出提取的圆
		for (int i = 0; i < 4; i++)
		{
			float* p = (float*)cvGetSeqElem(circles, i);
			CvPoint pt = cvPoint(cvRound(p[0]), cvRound(p[1]));
			prank[i] = pt;

			//cout << "圆心坐标x= " << cvRound(p[0]) << endl << "圆心坐标y= " << cvRound(p[1]) << endl;
			//cout << "半径=" << cvRound(p[2]) << endl;
			cvCircle(color, pt, cvRound(p[2]), CV_RGB(255, 0, 0), 1, 8, 0);
			cvNamedWindow(Filename, 0);
			cvShowImage(Filename, color);




		}
		//////////////////////////////////////////////////////排序

		sort(prank, 4);
		for (int i = 0; i < 4; i++)
			cout << prank[i].x << "   " << prank[i].y << endl;// 看排序的效果

		//////////////////////////////////////////////////////保存为txt文件
		ofstream write;
		write.open(Filename, ofstream::app);//模式为输出和追加
		for (int i = 0; i < 4; i++)
			write << prank[i].x << "   " << prank[i].y << endl;
		write.close();


}

void ExCircles(CvArr* dstleft, CvArr* dstright)
{
	CvMemStorage* storageleft = cvCreateMemStorage(0);
	CvMemStorage* storageright= cvCreateMemStorage(0);

	CvSeq* circlesleft = cvHoughCircles(dstleft, storageleft, CV_HOUGH_GRADIENT, 1, 80, 150, 15, 15, 20);
	CvSeq* circlesright = cvHoughCircles(dstright, storageright, CV_HOUGH_GRADIENT, 1, 80, 200, 15, 15, 20);

	if ((4==(circlesleft->total))&&( 4== (circlesright->total)))


	{
		SaveCircles(dstleft, "left.txt", circlesleft);

		SaveCircles(dstright, "right.txt",circlesright);

	}


};

