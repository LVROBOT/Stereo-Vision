
#include"Hough.h"
#include"CameraSptr.h"

MemBufferCollection::tMemBufferPtr   Pleft;
MemBufferCollection::tMemBufferPtr   Pright;

int main(int argc, char* argv[])

{
	OpenCamera();

	StartCamera();
	for (int i = 0; i < 10; i++)
	{
		GetImageBuffer(&Pright, &Pleft);

		Bismooth(Pleft, Pright);

		ExCircles(leftdst, rightdst);

	}
	
	cvWaitKey(0);
	CloseCamera();

	return 0;
}
