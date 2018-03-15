// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#define _WIN32_WINNT 0x0500
#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>
#include <CommCtrl.h>
#include <CommDlg.h>

#include <cmath>

#ifndef M_PI
#define M_PI	3.14159265358979323846
#endif

// TODO: reference additional headers your program requires here

#include <tisudshl.h>
#include <FilterFactory.h>
//>>