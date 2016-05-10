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

#define DEFAULT_LIFE			(3)
#define DEFAULT_BULLET			BULLET_SINGLE
#define DEFAULT_GUN_BULLET		(6)
#define DEFAULT_DOUBLE_BULLET	(2)
#define GUN_BULLET_MAX			(30)
#define DOUBLE_BULLET_MAX		(8)
#define REGENTIME_BALL_FAST		(2.0f)
#define REGENTIME_BALL			(11.0f)
#define REGENTIME_POLYGON		(17.0f)
#define REGENTIME_CLOCK			(33.0f)
#define REGENTIME_BLOCK			(5.0f)
#define REGENTIME_BULLET		(42.0f)
#define REGENCOUNT_BURST		(50)
#define SAFE_DEATHTIME			(2.4f)
#define CLOCK_ADDTIME			(5.0f)
#define LIFEBONUS_SCORE			(10000)

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
	SOUND_BGM_GAMEOVER,
	SOUND_BGM_BACK1,
	SOUND_BGM_BACK2,
	SOUND_BGM_BACK3,
	SOUND_BGM_BACK4,
	SOUND_BALL_BURST,
	SOUND_BALL_DEVIDE,
	SOUND_ITEM_BULLET,
	SOUND_ITEM_CLOCK,
	SOUND_ITEM_FOOD,
	SOUND_ITEM_LIFE,
	SOUND_LIFE_MINUS,
	SOUND_DIE,
	MAX_SOUND // 사운드 개수
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
	bgObject	m_UI;

	objBullet	m_Bullet[MAX_BULLET];
	objObject	m_Object[MAX_OBJECT];
	objEffect	m_Effect[MAX_EFFECT];
	objItem		m_Item[MAX_ITEM];

	float		m_TimeStartGame;
	float		m_TimeMakeBall;
	float		m_TimeMakePolygon;
	float		m_TimeMakeBlock;
	float		m_TimeMakeClock;
	float		m_TimeLevelUp;
	float		m_TimeDeath;
	float		m_TimeClock;
	float		m_TimeShield;
	float		m_TimeBullet;
	float		m_TimeClockAdd;

	float		m_fRegenBall;
	float		m_fRegenPolygon;
	float		m_fRegenClock;
	float		m_fRegenBlock;
	float		m_fRegenBullet;
	int			m_iCountBurst;
	int			m_iCountScore;

	int			m_CountObject;
	int			m_CountBullet;
	int			m_CountEffect;
	int			m_CountLife;
	int			m_CountItem;

	int			m_iDoubleBullet;
	int			m_iGunBullet;

public:
	GAME_STATE	m_GameState;
	BULLET_TYPE	m_BulletType;
	int			m_iHeroLevel;
	int			m_iScore;

public:
	int		CreateObject(OBJECT_TYPE iType, float fX, float fY, int iSize = 1);
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

