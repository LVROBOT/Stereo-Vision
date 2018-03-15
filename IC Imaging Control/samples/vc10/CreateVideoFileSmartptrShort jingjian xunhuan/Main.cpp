
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

	for (int i = 0; i<58;i++)
	{
		if (i < 50)
			continue;

		GetImageBuffer(&Pright, &Pleft);

		Bismooth(Pleft, Pright);

		cout << i << endl;
		ExCircles(leftdst, "left.txt");

		ExCircles(rightdst, "right.txt");
		
		cvWaitKey(0);
	}

		/*cvNamedWindow("1", 1);
		cvShowImage("1", leftdst);

		cvNamedWindow("2", 1);
		cvShowImage("2", rightdst);*/

		
		CloseCamera();


	

	return 0;
}
