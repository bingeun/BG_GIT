#pragma once
#include "bgStd.h"

class bgBitmap
{
public:
	HDC		m_hScreenDC;
	HDC		m_hMemDC;
	HBITMAP m_hBitmap;
	BITMAP	m_hBitInfo;

public:
	bool	Load(HDC hScreenDC, TCHAR* pFileName);

public:
	bgBitmap();
	virtual ~bgBitmap();
};

