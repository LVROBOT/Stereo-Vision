#pragma once
#define _WIN32_WINNT 0x0500
#include <windows.h>
#include <conio.h>
#include <iostream>
#include <tisudshl.h>
#include <memory>

#include "../Common/CmdHelper.h"
using namespace _DSHOWLIB_NAMESPACE;

static tFrameHandlerSinkPtr pSinkR;
static tFrameHandlerSinkPtr pSinkL;

extern std::shared_ptr<Grabber>grabberR;
extern std::shared_ptr<Grabber>grabberL;


bool OpenCamera();
bool StartCamera();
void SuspendCamera();
void CloseCamera();

bool GetImageBuffer(DShowLib::Grabber::tMemBufferPtr *bufferR, DShowLib::Grabber::tMemBufferPtr *bufferL);
bool openDeviceFromFile(_DSHOWLIB_NAMESPACE::Grabber& gr, const std::string& devStateFilename);