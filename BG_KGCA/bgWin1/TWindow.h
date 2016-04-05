#pragma once
#include <tchar.h>
#include <Windows.h>

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

class TWindow
{
public:
	HWND m_hWnd;
	RECT m_rtWindow;
	RECT m_rtClient;

public:
	bool SetWindow(HINSTANCE hInstance);

public:
	TWindow();
	virtual ~TWindow();
};

