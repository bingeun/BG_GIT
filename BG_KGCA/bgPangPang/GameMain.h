#pragma once
#include "bgStd.h"
#include "bgSys.h"
#include "bgCore.h"
#include "bgCollision.h"
#include "bgFrameMgr.h"
#include "bgSound.h"

#include "objHero.h"
#include "objGround.h"
#include "objBullet.h"
#include "objObject.h"
#include "objEffect.h"
#include "objItem.h"
#include "objFont.h"

#define CLIENT_W	(800)
#define CLIENT_H	(600)

// 시작할 때 기본 무기 종류 = BULLET_SINGLE, BULLET_DOUBLE, BULLET_FIXED, BULLET_GUN
#define DEFAULT_LIFE		(3)
#define DEFAULT_BULLET		BULLET_SINGLE
#define REGENTIME_BALL		(5.0f)
#define REGENTIME_POLYGON	(8.5f)
#define SAFE_DEATHTIME		(2.4f)

enum GAME_STATE
{
	STATE_MAIN = 0,
	STATE_SINGLE,
	STATE_NETWORK,
	STATE_EXIT,
};

enum GAME_SOUND
{
	SOUND_BGM_MAIN = 0,
	SOUND_BGM_BACK1,
	SOUND_BGM_BACK2,
	SOUND_BGM_BACK3,
	SOUND_BGM_BACK4,
	SOUND_BALL_BURST,
	SOUND_BALL_DEVIDE,
	SOUND_ITEM_EAT,
	SOUND_LIFE_MINUS,
	SOUND_DIE,
	MAX_SOUND // 사운드 갯수
};


class GameMain : public bgCore
{
public:
	HDC			m_hScreenDC;
	HDC			m_hOffScreenDC;
	HBITMAP		m_hOffScreenBitmap;
	bgCollision	m_Collision;
	bgSound		m_Sound;
 	int			m_arySound[MAX_SOUND];

	objHero		m_Hero;
	objGround	m_Ground;
	objGround	m_Gameover;
	objFont		m_Font;
	objBullet	m_Bullet[MAX_BULLET];
	objObject	m_Object[MAX_OBJECT];
	objEffect	m_Effect[MAX_EFFECT];
	objItem		m_Item[MAX_ITEM];
	int			m_aryLife[MAX_LIFE];

	float		m_TimeStartGame;
	float		m_TimeMakeBall;
	float		m_TimeMakePolygon;
	float		m_TimeMakeBlock;
	float		m_TimeMakeClock;
	float		m_TimeLevelUp;
	float		m_TimeDeath;

	int			m_CountObject;
	int			m_CountBullet;
	int			m_CountEffect;
	int			m_CountLife;
	int			m_CountItem;

public:
	GAME_STATE	m_GameState;
	BULLET_TYPE	m_BulletType;
	int			m_iHeroLevel;
	int			m_iScore;

public:
	void	CreateObject(OBJECT_TYPE iType, float fX, float fY, int iSize = 1);
	void	CreateBullet(BULLET_TYPE iType, float fX, float fY);
	void	CreateEffect(EFFECT_TYPE iType, float fX, float fY);
	int		CreateItem(ITEM_TYPE iType, float fX, float fY);
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

