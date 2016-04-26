#pragma once
#include "bgStd.h"
#include "bgSys.h"
#include "bgCore.h"
#include "bgSpriteMgr.h"

#include "objHero.h"
#include "objGround.h"

#define BOARD_W		(50)
#define BOARD_H		(34)
#define BLOCK_W		(15)
#define BLOCK_H		(15)
#define CLIENT_W	(800)
#define CLIENT_H	(600)
#define BOARD_X		(25)
#define BOARD_Y		(25)
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

	float		m_fX;
	float		m_fY;

	GAME_STATE	m_GameState;

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

