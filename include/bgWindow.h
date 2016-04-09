#pragma once
#include "bgStd.h"

class bgWindow
{
public:
	HINSTANCE	m_hInstance;
	HWND		m_hWnd;
	RECT		m_rtWindow;
	RECT		m_rtClient;
	int			m_iWidth;
	int			m_iHeight;

public:
	void	SetRect(int iWidth, int iHeight);
	bool	SetWindow(HINSTANCE hInstance, TCHAR* titleName = L"BG Project", int iX = 0, int iY = 0, int iWidth = 800, int iHeight = 600);

public:
	bgWindow();
	virtual ~bgWindow();
};

