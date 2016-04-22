#pragma once
#include "bgCore.h"
#include "bgGround.h"
#include "bgHero.h"
#include "bgEnemy.h"
#include "bgSpriteMgr.h"

class GameMain : public bgCore
{
public:
	HDC			m_hScreenDC;
	HDC			m_hOffScreenDC;
	HBITMAP		m_hOffScreenBitmap;

	//bgGround	m_Ground;
	bgHero		m_Hero;
	//bgEnemy		m_Enemy;

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

