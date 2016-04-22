#pragma once
#include "bgSpriteMgr.h"

class bgObject
{
public:
	bgSprite*	m_pSprite;
	bgBitmap*	m_pBitmap;
	INT		m_iSprite;
	INT		m_iBitmap;
	HDC		m_hScreenDC;
	HDC		m_hOffScreenDC;
	POINT	m_posObject;
	RECT	m_rectObject;
	HBRUSH	m_hBrush;
	HBRUSH	m_hOldBrush;
	float	m_fSpeed;
	float	m_fDirection;

public:
	bool	Load(HDC hScreenDC, HDC hOffScreenDC, TCHAR* pszName, TCHAR* pszNameMask = NULL);
	void	SetObject(RECT rect, POINT pos, float fSpeed = 10.0f);

	void	Left();
	void	Right();
	void	Up();
	void	Down();

public:
	bool	Init();
	bool	Frame();
	bool	Render();
	bool	Release();

public:
	bgObject();
	virtual ~bgObject();
};

