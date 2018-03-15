// DemoFilters.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"

#include "RotateTransform.h"
#include "DeNoiseTransform.h"
#include "SnapFilter.h"
#include "BinarizationFilter.h"

/*
 *	Global variable saving the instance handle of this DLL.
 */
HINSTANCE g_hInst;

/*
 *	Save the hModule because it is needed to load dialog resources from this DLL
 */
BOOL APIENTRY DllMain( HANDLE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved )
{
	g_hInst = (HINSTANCE)hModule;
    return TRUE;
}

/*
 *	These macros generate an exported function that allows IC Imaging Control's filter loader
 *	to enumerate and create instances of the filters:
 */
FILTERDLL_BEGIN_EXPORT()
	FILTERDLL_REGISTER_FILTER(CRotateTransform)
	FILTERDLL_REGISTER_FILTER(CDeNoiseTransform)
	FILTERDLL_REGISTER_FILTER(CSnapFilter)
	FILTERDLL_REGISTER_FILTER(CBinarizationFilter)
FILTERDLL_END_EXPORT()
//>>