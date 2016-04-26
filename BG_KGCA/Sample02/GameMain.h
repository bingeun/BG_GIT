#pragma once
#include "bgCore.h"
#include "bgHero.h"
#include "bgEnemy.h"
#include "bgGround.h"
#include "bgSpriteMgr.h"

class GameMain : public bgCore
{
public:
	HDC			m_hScreenDC;
	HDC			m_hOffScreenDC;
	HBITMAP		m_hOffScreenBitmap;

	bgHero		m_Hero;
	bgGround	m_Ground;

	float		m_fX;
	float		m_fY;

public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();

public:
	GameMain();
	virtual ~GameMain();
};

