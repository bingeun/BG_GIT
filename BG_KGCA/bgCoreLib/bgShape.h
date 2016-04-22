#pragma once
#include "bgStd.h"
#include "bgBitmapMgr.h"
#include "bgSpriteMgr.h"

class bgShape
{
public:
	HDC			m_hScreenDC;
	HDC			m_hOffScreenDC;

	bgBitmap*	m_pBitmap;
	int			m_iBitmap;
	bool		m_bMask;
	HBRUSH		m_hBrush;
	HBRUSH		m_hOldBrush;
	POINT		m_posObject;
	RECT		m_rectObject;
	RECT		m_rectCollision;

public:
	virtual void	SetPos(POINT pos);
	virtual void	SetRect(RECT rect, POINT pos);
	virtual bool	Load(HDC hScreenDC, HDC hOffScreenDC, TCHAR* pszNameColor, TCHAR* pszNameMask);

	virtual bool	Init();
	virtual bool	Frame();
	virtual bool	Render();
	virtual bool	Release();

public:
	bgShape();
	virtual ~bgShape();
};

