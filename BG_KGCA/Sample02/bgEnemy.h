#pragma once
#include "bgStd.h"

class bgBitmap
{
public:
	HDC		m_hScreenDC;
	HDC		m_hOffScreenDC;
	HDC		m_hMemDC;
	HBITMAP m_hBitmap;
	HBITMAP m_hOldBitmap;
	BITMAP	m_hBitInfo;

public:
	bool	Load(HDC hScreenDC, HDC hOffScreenDC, TCHAR* pFileName);
	bool	Init();
	bool	Frame();
	bool	Render();
	bool	Release();

public:
	bgBitmap();
	virtual ~bgBitmap();
};

