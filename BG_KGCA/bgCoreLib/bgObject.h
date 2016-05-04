#pragma once
#include "bgFrameMgr.h"
#include "bgSprite.h"

class bgObject
{
public:
	HDC		m_hOffScreenDC;
	HBRUSH	m_hBrush;
	HBRUSH	m_hOldBrush;

	bgSprite	m_Sprite;
	bgBitmap*	m_pBitmap;
	bgFrame*	m_pFrame;
	INT		m_iBitmap;
	INT		m_iFrame;
	POINT	m_posObject;
	RECT	m_rectObject;

public:
	float	m_fPosX;
	float	m_fPosY;
	float	m_fSpeed;
	float	m_fDirection;

public:
	void	SetDC(HDC hdc) { m_hOffScreenDC = hdc; }
	void	SetBitmap(TCHAR* pszBitmap);
	void	SetSprite(TCHAR* pszSprite);

	void	SetObject(float fPosX, float fPosY, float fSpeed);

public:
	virtual bool	Init();
	virtual bool	Frame();
	virtual bool	Render();
	virtual bool	Release();

public:
	bgObject();
	virtual ~bgObject();
};

