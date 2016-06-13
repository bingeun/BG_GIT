#pragma once
#include "bgStd.h"
#include "bgSys.h"
#include "bgCore.h"
#include "bgFrameMgr.h"
#include "bgSound.h"
#include "bgUdpSocketSvr.h"
#include "bgUdpSocketClnt.h"

#include "bgClient.h"

#include "objBack.h"
#include "objUI.h"

#define CLIENT_W	(1024)
#define CLIENT_H	(768)

enum GAME_STATE
{
	GAMESTATE_MAIN = 0,
	GAMESTATE_LOBBY,
	GAMESTATE_GAMEROOM,
	GAMESTATE_SINGLE,
	GAMESTATE_NETWORK,
	GAMESTATE_NETWORK_SERVER,
	GAMESTATE_NETWORK_CLIENT,
	GAMESTATE_EXIT,
};

enum PLAY_STATE
{
	PLAYSTATE_WAIT = 0,
	PLAYSTATE_PLAY,
	PLAYSTATE_GAMEOVER,
	PLAYSTATE_TRAIN,
};

enum GAME_SOUND
{
	// BGM 목록
	SOUND_BGM_MAIN = 0,
	SOUND_BGM_GAMEOVER,
	SOUND_BGM_BACK1,
	SOUND_BGM_BACK2,
	SOUND_BGM_BACK3,
	SOUND_BGM_BACK4,
	// 게임진행 외적인 유저행동 효과음
	SOUND_PLAYER_IN,
	SOUND_PLAYER_OUT,
	SOUND_PLAYER_READY,
	SOUND_PLAYER_PLAY,
	SOUND_PLAYER_GAMEOVER,
	SOUND_PLAYER_CHAT,
	SOUND_PLAYER_MOUSEOVER,
	SOUND_PLAYER_CLICK,
	// 게임진행중 키입력 효과음
	SOUND_BLOCK_MOVE,
	SOUND_BLOCK_DOWN,
	SOUND_BLOCK_ROTATE,
	SOUND_BLOCK_DROP,
	// 게임중 상태 효과음
	SOUND_BOARD_DEL1,
	SOUND_BOARD_DEL2,
	SOUND_BOARD_DEL3,
	SOUND_BOARD_DEL4,
	// 아이템 사용 효과음
	SOUND_ITEM_ADD,
	SOUND_ITEM_SLASH,
	SOUND_ITEM_TWIST,
	SOUND_ITEM_DARK,
	SOUND_ITEM_SUB,
	SOUND_ITEM_STRAIGHT,
	SOUND_ITEM_DROP,
	SOUND_ITEM_CLEAR,
	SOUND_ITEM_SHIELD,
	SOUND_ITEM_CHANGE,
	MAX_SOUND // 사운드 개수
};

class GameMain : public bgCore
{
public:
	HDC			m_hScreenDC;
	HDC			m_hOffScreenDC;
	HBITMAP		m_hOffScreenBitmap;

	objBack		m_Back;
	objUI		m_UI;
	bgSound		m_Sound;
	int			m_arySound[MAX_SOUND];

	int			m_iMyClientID;
	bgClient	m_NetrisClnt;

	GAME_STATE	m_GameState;
	PLAY_STATE	m_PlayState;

	float		m_fTimeStartGame;
	float		m_fTimeGameover;

public:
	bgUdpSocketSvr	m_Udp;

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

	bool ServerInit();
	bool ServerFrame();
	bool ServerRender();
	bool ServerExit();

	bool ClientInit();
	bool ClientFrame();
	bool ClientRender();
	bool ClientExit();
/*
	bool LobbyInit();
	bool LobbyFrame();
	bool LobbyRender();
	bool LobbyExit();

	bool GameroomInit();
	bool GameroomFrame();
	bool GameroomRender();
	bool GameroomExit();
*/
public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();

	GameMain();
	virtual ~GameMain();
};
