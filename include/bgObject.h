#pragma once
#include "bgSpriteMgr.h"

#define DEFAULT_SPEED (30.0f)

class bgObject
{
public:
	HDC		m_hOffScreenDC;
	HBRUSH	m_hBrush;
	HBRUSH	m_hOldBrush;

	bgSprite*	m_pSprite;
	bgBitmap*	m_pBitmap;
	INT		m_iSprite;
	INT		m_iBitmap;
	POINT	m_posObject;
	RECT	m_rectObject;

public:
	float	m_fPosX;
	float	m_fPosY;
	float	m_fSpeed;
	float	m_fDirection;

public:
	void	SetDC(HDC hdc) { m_hOffScreenDC = hdc; }
	void	SetObject(float fPosX, float fPosY, float fSpeed = DEFAULT_SPEED);

	void	Left();
	void	Right();
	void	Up();
	void	Down();
	void	SpeedUp(float fSpeedUp = 1.0f);
	void	SpeedDown(float fSpeedDown = 1.0f);

public:
	virtual bool	Init();
	virtual bool	Frame();
	virtual bool	Render();
	virtual bool	Release();

public:
	bgObject();
	virtual ~bgObject();
};

