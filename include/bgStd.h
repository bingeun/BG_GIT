#pragma once
#include <Windows.h>
#include <tchar.h>
#include <math.h>
#include <map>
#include <list>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>

using namespace std;
#pragma comment( lib, "ws2_32.lib")
#pragma comment( lib, "winmm.lib")

#define RadianToDegree(fAngle) (fAngle * (3.141592f / 180.0f))
#define DegreeToRadian(fAngle) (fAngle * (180.0f / 3.141592f))

template <class T> class bgSingleton
{
public:
	static T& GetInstance()
	{
		static T theSingleton;
		return theSingleton;
	}
};
