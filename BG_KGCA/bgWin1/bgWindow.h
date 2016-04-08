#pragma once
#include "bgStd.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

class bgWindow
{
public:
	HWND m_hWnd;
	RECT m_rtWindow;
	RECT m_rtClient;

public:
	bool SetWindow(HINSTANCE hInstance);

public:
	bgWindow();
	virtual ~bgWindow();
};

