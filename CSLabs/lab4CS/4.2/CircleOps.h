#pragma once
#include <utility>
#include <limits.h>

#define DLL_EXPORTS extern "C" __declspec(dllexport) double

DLL_EXPORTS __stdcall Perimeter(double r);
DLL_EXPORTS __cdecl Area(double r);
DLL_EXPORTS __stdcall SectorArea(double r, int angle);