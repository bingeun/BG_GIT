#pragma once
#include "bgCore.h"
#include "bgBitmap.h"

class GameMain : public bgCore
{
public:
	HDC			m_hScreenDC;
	HDC			m_hOffScreenDC;
	HBITMAP		m_h;

	bgObject	m_Background;
	bgObject	m_Hero;

	float		m_iX;
	float		m_iY;

public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();

public:
	GameMain();
	virtual ~GameMain();
};

