#pragma once
#include <Windows.h>
#include "bgWindow.h"

// bgWindow - ������ ���� ��������
extern HWND			g_hWnd;
extern HINSTANCE	g_hInstance;
extern RECT			g_rtWindow;

// bgTimer - Ÿ�̸� ���� ��������
extern int			g_iFPS;
extern float		g_fSPF;
extern float		g_fAccumulation;
