#pragma once
#include "bgStd.h"
#include "bgSys.h"
#include "bgCore.h"
#include "bgCollision.h"
#include "bgSpriteMgr.h"
// SOUND ##### #include "bgSound.h"

#include "objHero.h"
#include "objGround.h"
#include "objBullet.h"
#include "objObject.h"
#include "objEffect.h"

#define CLIENT_W	(800)
#define CLIENT_H	(600)

// 시작할 때 기본 무기 종류 = BULLET_SINGLE, BULLET_DOUBLE, BULLET_FIXED, BULLET_GUN
#define DEFAULT_BULLET		BULLET_SINGLE
#define REGENTIME_BALL		(5.0f)
#define REGENTIME_POLYGON	(8.5f)
#define SAFE_DEATHTIME		(3.0f)

enum GAME_STATE
{
	STATE_MAIN = 0,
	STATE_SINGLE,
	STATE_NETWORK,
	STATE_EXIT,
};

/*
enum GAME_SOUND
{
	SOUND_BGM = 0,
	SOUND_BALL_BURST,
	SOUND_BALL_DEVIDE,
	SOUND_LIFE_MINUS,
	SOUND_DIE,
	MAX_SOUND // 사운드 갯수
};
*/

class GameMain : public bgCore
{
public:
	HDC			m_hScreenDC;
	HDC			m_hOffScreenDC;
	HBITMAP		m_hOffScreenBitmap;
	bgCollision	m_Collision;
	// SOUND #####	bgSound		m_Sound;
	// SOUND ##### 	int			m_arySound[MAX_SOUND];

	objHero		m_Hero;
	objGround	m_Ground;
	objGround	m_Gameover;
	objBullet	m_Bullet[MAX_BULLET];
	objObject	m_Object[MAX_OBJECT];
	objEffect	m_Effect[MAX_EFFECT];

	float		m_TimeStartGame;
	float		m_TimeMakeBall;
	float		m_TimeMakePolygon;
	float		m_TimeMakeBlock;
	float		m_TimeMakeClock;
	float		m_TimeDeath;

	GAME_STATE	m_GameState;
	BULLET_TYPE	m_BulletType;
	int			m_CountObject;
	int			m_CountBullet;
	int			m_CountEffect;
	int			m_CountLife;

public:
	void	CreateObject(OBJECT_TYPE iType, float fX, float fY, int iSize = 1);
	void	CreateBullet(BULLET_TYPE iType, float fX, float fY);
	void	CreateEffect(EFFECT_TYPE iType, float fX, float fY);
	void	FrameKey();
	void	FrameObject();
	void	FrameTimer();
	void	FrameCollide();

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

