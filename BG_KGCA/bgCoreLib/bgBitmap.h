#pragma once
#include "bgStd.h"
#include "bgSys.h"

class bgBitmap
{
public:
	int		m_iIndex;
	TCHAR	m_pszName[MAX_PATH];
	HDC		m_hMemDC;
	HDC		m_hScreenDC;
	BITMAP	m_BitmapInfo;
	HBITMAP m_hBitmap;
	HBITMAP m_hOldBitmap;

public:
	int		GetIndex() { return m_iIndex; }
	TCHAR*	GetName() { return m_pszName; }
	void	SetScreenDC(HDC hdc) { m_hScreenDC = hdc; }

	bool	Load(TCHAR* pszName);
	HBITMAP	GetRotationBitmap(HDC hdc, RECT& rect, int iWidth, int iHeight, float fAngle = 0);
	bool	Draw(HDC hdc, POINT pos, RECT rect, DWORD mode = SRCCOPY, float fAngle = 0);

	bool	Init();
	bool	Frame();
	bool	Render();
	bool	Release();

public:
	bgBitmap();
	virtual ~bgBitmap();
};
