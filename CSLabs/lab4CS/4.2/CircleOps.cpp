// dllmain.cpp : Определяет точку входа для приложения DLL.
#include "pch.h"

#include <math.h>
#include <utility>
#include <limits.h>

#define DLL_EXPORTS extern "C" __declspec(dllexport) double

DLL_EXPORTS __stdcall Perimeter(double r)
{
	return 2.0 * M_PI * r;
}

DLL_EXPORTS __cdecl Area(double r)
{
	return M_PI * pow(r, 2.0);
}

DLL_EXPORTS __stdcall SectorArea(double r, int angle)
{
	return M_PI * pow(r, 2.0) * ((double)angle) / 360.0;
}