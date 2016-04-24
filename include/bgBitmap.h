#pragma once
#include "bgStd.h"
#include "bgSys.h"

class bgBitmap
{
public:
	HDC		m_hOffScreenDC;
	HBITMAP m_hOldBitmap;
	bool	m_bMask;

	wstring	m_szName;
	HDC		m_hMemDC;
	HBITMAP m_hBitmap;
	BITMAP	m_BitmapInfo;

	wstring	m_szNameMask;
	HDC		m_hMemDCMask;
	HBITMAP m_hBitmapMask;
	BITMAP	m_BitmapInfoMask;

public:
	void	SetDC(HDC hdc) { m_hOffScreenDC = hdc; }

	bool	Load(TCHAR* pszName, TCHAR* pszNameMask = NULL);
	bool	Load(DWORD dwBitmap);
	HBITMAP	GetRotationBitmap(HDC hdc, RECT& rect, int iWidth, int iHeight, float fAngle = 0.0f);
	bool	Draw(HDC hdc, POINT pos, RECT rect, float fAngle = 0.0f, DWORD dwMode = SRCCOPY);

	bool	Init();
	bool	Frame();
	bool	Render();
	bool	Release();

public:
	bgBitmap();
	virtual ~bgBitmap();
};
