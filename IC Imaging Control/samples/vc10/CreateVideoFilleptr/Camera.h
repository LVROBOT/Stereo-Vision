
//#define _WIN32_WINNT 0x0500

//#include "ICImagingControl\include\tisudshl.h" 


//#include <windows.h>
//#include <conio.h>
//#include <iostream>
#include <tisudshl.h>
#include "../Common/CmdHelper.h"///////��ʾ��һ��Ŀ¼

bool OpenCamera();
bool StartCamera();
void SuspendCamera();
void CloseCamera();

bool GetImageBuffer(DShowLib::Grabber::tMemBufferPtr* bufferR, DShowLib::Grabber::tMemBufferPtr* bufferL);

