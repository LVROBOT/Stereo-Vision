
#include"Hough.h"
#include"CameraSptr.h"
#include <WinDef.h>
#include <cv.h>
#include <highgui.h>

using namespace cv;

MemBufferCollection::tMemBufferPtr   Pleft;
MemBufferCollection::tMemBufferPtr   Pright;

int main(int argc, char* argv[])

{
	OpenCamera();



	StartCamera();


	for (int i = 0; i <1;i++)
	{

		GetImageBuffer(&Pright, &Pleft);

		Bismooth(Pleft, Pright);

		ExCircles(leftdst, "left.txt");

		ExCircles(rightdst, "right.txt");
	}

		/*cvNamedWindow("1", 1);
		cvShowImage("1", leftdst);

		cvNamedWindow("2", 1);
		cvShowImage("2", rightdst);*/

		waitKey(0);
		CloseCamera();


	

	return 0;
}
