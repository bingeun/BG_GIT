#pragma once
#include <Windows.h>
#include "bgWindow.h"

// bgWindow - 윈도우 관련 전역변수
extern HWND			g_hWnd;
extern HINSTANCE	g_hInstance;
extern RECT			g_rtWindow;

// bgCore - 화면 관련 전역변수
extern HDC			g_hScreenDC;
extern HDC			g_hOffScreenDC;

// bgTimer - 타이머 관련 전역변수
extern int			g_iFPS;
extern float		g_fSPF;
extern float		g_fAccumulation;
