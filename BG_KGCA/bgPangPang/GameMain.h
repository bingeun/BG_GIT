#pragma once
#include "bgStd.h"
#include "bgSys.h"
#include "bgCore.h"
#include "bgSpriteMgr.h"

#include "objHero.h"
#include "objGround.h"
#include "objBullet.h"

#define BOARD_W		(50)
#define BOARD_H		(34)
#define BLOCK_W		(15)
#define BLOCK_H		(15)
#define CLIENT_W	(800)
#define CLIENT_H	(600)
#define BOARD_X		(25)
#define BOARD_Y		(25)
#define HERO_W		(45)
#define HERO_H		(60)
// (CLIENT_W - ((BOARD_W * BLOCK_W) / 2))

enum GAME_STATE
{
	STATE_MAIN = 0,
	STATE_SINGLE,
	STATE_NETWORK,
	STATE_EXIT,
};

class GameMain : public bgCore
{
public:
	HDC			m_hScreenDC;
	HDC			m_hOffScreenDC;
	HBITMAP		m_hOffScreenBitmap;

	objHero		m_Hero;
	objGround	m_Ground;
	vector<objBullet> m_Bullet;
	vector<objBullet>::iterator m_iterBullet;

	GAME_STATE	m_GameState;
	BULLET_TYPE	m_BulletType;
	int			m_CountBullet;

public:
	void	CreateBullet(BULLET_TYPE iType, float fX, float fY);

public:
	bool MainInit();
	bool MainFrame();
	bool MainRender();
	bool MainExit();

	bool SingleInit();
	bool SingleFrame();
	bool SingleRender();
	bool SingleExit();

	bool NetworkInit();
	bool NetworkFrame();
	bool NetworkRender();
	bool NetworkExit();

	bool Init();
	bool Frame();
	bool Render();
	bool Release();

public:
	GameMain();
	virtual ~GameMain();
};

