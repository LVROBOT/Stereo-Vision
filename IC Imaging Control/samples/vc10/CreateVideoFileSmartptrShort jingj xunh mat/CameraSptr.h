#pragma once
#include <windows.h>
#include <conio.h>
#include <iostream>
#include <tisudshl.h>
#include <memory>

#include "../Common/CmdHelper.h"
using namespace _DSHOWLIB_NAMESPACE;

bool OpenCamera();
bool StartCamera();
void SuspendCamera();
void CloseCamera();
bool GetImageBuffer(MemBufferCollection::tMemBufferPtr * bufferR, MemBufferCollection::tMemBufferPtr *bufferL);
bool openDeviceFromFile(_DSHOWLIB_NAMESPACE::Grabber& gr, const std::string& devStateFilename);