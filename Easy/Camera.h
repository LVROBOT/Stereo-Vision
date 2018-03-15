#pragma once
#pragma   warning(disable: 4996)
#include <windows.h>
#include <conio.h>
#include <iostream>
#include <memory>
#include "tisudshl.h"//相机自带头文件
#include "IC Imaging Control\samples\vc10\Common\CmdHelper.h"//相机自带头文件

using namespace _DSHOWLIB_NAMESPACE;

bool OpenCamera();
bool StartCamera();
void SuspendCamera();
void CloseCamera();
bool GetImageBuffer(MemBufferCollection::tMemBufferPtr * bufferR, MemBufferCollection::tMemBufferPtr *bufferL);
bool openDeviceFromFile(_DSHOWLIB_NAMESPACE::Grabber& gr, const std::string& devStateFilename);
