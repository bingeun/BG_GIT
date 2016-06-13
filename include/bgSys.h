#pragma once
#include <Windows.h>
#include "bgWindow.h"

// bgWindow - 윈도우 관련 전역변수
extern HWND			g_hWnd;
extern HINSTANCE	g_hInstance;
extern RECT			g_rtWindow;

// bgTimer - 타이머 관련 전역변수
extern int			g_iFPS;
extern float		g_fSPF;
extern float		g_fAccumulation;
