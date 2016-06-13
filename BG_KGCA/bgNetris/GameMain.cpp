#include "GameMain.h"


bool GameMain::Init()
{
	m_hScreenDC = GetDC(m_hWnd);
	m_hOffScreenDC = CreateCompatibleDC(m_hScreenDC);
	m_hOffScreenBitmap = CreateCompatibleBitmap(m_hScreenDC, CLIENT_W, CLIENT_H);
	SelectObject(m_hOffScreenDC, m_hOffScreenBitmap);

	m_Sound.Init();
	m_arySound[SOUND_BGM_MAIN] = m_Sound.Load("../../data/bgNetris/bgm_main.mp3", false);
	m_arySound[SOUND_BGM_BACK1] = m_Sound.Load("../../data/bgNetris/bgm_back1.mid", false);
	m_arySound[SOUND_BGM_BACK2] = m_Sound.Load("../../data/bgNetris/bgm_back2.mid", false);
	m_arySound[SOUND_BGM_BACK3] = m_Sound.Load("../../data/bgNetris/bgm_back3.mid", false);
	m_arySound[SOUND_BGM_BACK4] = m_Sound.Load("../../data/bgNetris/bgm_back4.mid", false);

	m_Sound.SetLoop(SOUND_BGM_MAIN);
	m_Sound.SetLoop(SOUND_BGM_BACK1);
	m_Sound.SetLoop(SOUND_BGM_BACK2);
	m_Sound.SetLoop(SOUND_BGM_BACK3);
	m_Sound.SetLoop(SOUND_BGM_BACK4);

	m_arySound[SOUND_BGM_GAMEOVER] = m_Sound.Load("../../data/bgNetris/bgm_gameover.wav", false);
	m_arySound[SOUND_PLAYER_GAMEOVER] = m_Sound.Load("../../data/bgNetris/gameover.wav", false);

	I_FrameMgr.Add(L"../../data/bgNetris/block_big.txt");
	I_FrameMgr.Add(L"../../data/bgNetris/block_small.txt");

	m_Back.Init();
	m_UI.Init();

	m_GameState = GAMESTATE_MAIN;
	m_PlayState = PLAYSTATE_WAIT;
	MainInit();

	return true;
}

bool GameMain::Frame()
{
	switch (m_GameState)
	{
	case GAMESTATE_NETWORK_CLIENT:
		ClientFrame();
		break;
	case GAMESTATE_NETWORK_SERVER:
		ServerFrame();
		break;
	case GAMESTATE_NETWORK:
		NetworkFrame();
		break;
	case GAMESTATE_SINGLE:
		SingleFrame();
		break;
/*
	case GAMESTATE_GAMEROOM:
		GameroomFrame();
		break;
	case GAMESTATE_LOBBY:
		LobbyFrame();
		break;
*/
	case GAMESTATE_MAIN:
		MainFrame();
		break;
	case GAMESTATE_EXIT:
		PostQuitMessage(0); // 메세지 큐 제일 뒤에 WM_QUIT 를 추가
		break;
	}
	m_Sound.Frame();
	return true;
}

bool GameMain::Render()
{
	switch (m_GameState)
	{
	case GAMESTATE_NETWORK_CLIENT:
		ClientRender();
		break;
	case GAMESTATE_NETWORK_SERVER:
		ServerRender();
		break;
	case GAMESTATE_NETWORK:
		NetworkRender();
		break;
	case GAMESTATE_SINGLE:
		SingleRender();
		break;
/*
	case GAMESTATE_GAMEROOM:
		GameroomRender();
		break;
	case GAMESTATE_LOBBY:
		LobbyRender();
		break;
*/
	case GAMESTATE_MAIN:
		MainRender();
		break;
	}
	return true;
}

bool GameMain::Release()
{
	m_Sound.Release();
	m_Back.Release();
	m_UI.Release();

	ReleaseDC(m_hWnd, m_hOffScreenDC);
	ReleaseDC(m_hWnd, m_hScreenDC);
	return true;
}

GameMain::GameMain()
{
}

GameMain::~GameMain()
{
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstatnce, LPWSTR lpCmdLine, int nCmdShow)
{
	GameMain win;
	if (win.SetWindow(hInstance, L"BG Project", 0, 0, CLIENT_W, CLIENT_H) == true)
	{
		win.CenterWindow();
		win.Run();
	}
	return 0;
}
