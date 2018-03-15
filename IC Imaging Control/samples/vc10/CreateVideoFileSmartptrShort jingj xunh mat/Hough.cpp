#include"Hough.h"



Mat  leftdst ;//修改
Mat  rightdst ;//修改

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

void Smooth(const Mat & src, Mat dst)

{


	//cvAdaptiveThreshold(src, dst, 200, CV_ADAPTIVE_THRESH_MEAN_C, CV_THRESH_BINARY, 3, 5);////自适应阈值

	adaptiveThreshold(src, dst, 200, CV_ADAPTIVE_THRESH_GAUSSIAN_C, CV_THRESH_BINARY, 17, 15);////自适应阈值

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
	Mat leftRGB(1280, 960, IPL_DEPTH_8U, 3);//是三通道的//修改
	Mat rightRGB(1280, 960, IPL_DEPTH_8U, 3);////////////////////修改

	Mat leftImage(1280, 960, IPL_DEPTH_8U, 1);//修改
	Mat rightImage(1280, 960, IPL_DEPTH_8U, 1);//修改


	leftRGB.data = (uchar*)(Pleft->getPtr());//内部缓存区的指针，返回_UDSHL_EXP_API BYTE*	
	rightRGB.data = (uchar*)(Pright->getPtr());/////////////

	cvtColor(leftRGB, leftImage, CV_RGB2GRAY);/////////////////通道个数存在问题
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

	Mat color;//////////////////////////////////////////////////////////修改
	cvtColor(dst, color, CV_GRAY2RGB);//转化成三通道
	
		//auto Cir_total = circles.total;//////////////////可以放在外面
	//	cout << Filename << " " << Cir_total<<endl;//调试用的
	    // vector<CvPoint> prank(Cir_total);//定义向量 大小不一定////可以


		 cout << circles << endl;
	
	
		// /////调试用  画出提取的圆
		// for ( i = 0; i < Cir_total; i++)
		//{
		//	Point pt = circles();
		//	prank[i] = pt;
		//	
		//		//cout << "圆心坐标x= " << cvRound(p[0]) << endl << "圆心坐标y= " << cvRound(p[1]) << endl;
		//		//cout << "半径=" << cvRound(p[2]) << endl;
		//		circle(color, pt, cvRound(p[2]), CV_RGB(255, 0, 0), 1, 8, 0);
		//		namedWindow(Filename, 0);
		//		imshow(Filename, color);

		//		
		//	
	
		//}
		//////////////////////////////////////////////////////排序
	
		//sort(prank, Cir_total);
		//for (int i = 0; i < Cir_total; i++)
		//	cout << prank[i].x << "   " << prank[i].y << endl;// 看排序的效果
	
		////////////////////////////////////////////////////////保存为txt文件
		//ofstream write;
		//write.open(Filename,ofstream::app);//模式为输出和追加
		//for (int i = 0; i < Cir_total; i++)
		//	write << prank[i].x << "   " << prank[i].y << endl;
		//write.close();


}

