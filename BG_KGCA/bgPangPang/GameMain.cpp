#include "GameMain.h"

bool GameMain::Init()
{
	m_hScreenDC = GetDC(m_hWnd);
	m_hOffScreenDC = CreateCompatibleDC(m_hScreenDC);
	m_hOffScreenBitmap = CreateCompatibleBitmap(m_hScreenDC, CLIENT_W, CLIENT_H);
	SelectObject(m_hOffScreenDC, m_hOffScreenBitmap);

	m_Sound.Init();
	m_arySound[SOUND_BGM_MAIN]		= m_Sound.Load("../../data/bgPangPang/bgm_main.mp3", false);
	m_arySound[SOUND_BGM_GAMEOVER]	= m_Sound.Load("../../data/bgPangPang/bgm_gameover.wav", false);
	m_arySound[SOUND_BGM_BACK1]		= m_Sound.Load("../../data/bgPangPang/bgm_back1.mid", false);
	m_arySound[SOUND_BGM_BACK2]		= m_Sound.Load("../../data/bgPangPang/bgm_back2.mid", false);
	m_arySound[SOUND_BGM_BACK3]		= m_Sound.Load("../../data/bgPangPang/bgm_back3.mid", false);
	m_arySound[SOUND_BGM_BACK4]		= m_Sound.Load("../../data/bgPangPang/bgm_back4.mid", false);
	m_arySound[SOUND_BALL_BURST]	= m_Sound.Load("../../data/bgPangPang/ball_burst.wav", false);
	m_arySound[SOUND_BALL_DEVIDE]	= m_Sound.Load("../../data/bgPangPang/ball_devide.wav", false);
	m_arySound[SOUND_ITEM_BULLET]	= m_Sound.Load("../../data/bgPangPang/item_bullet.wav", false);
	m_arySound[SOUND_ITEM_CLOCK]	= m_Sound.Load("../../data/bgPangPang/item_clock.wav", false);
	m_arySound[SOUND_ITEM_FOOD]		= m_Sound.Load("../../data/bgPangPang/item_food.wav", false);
	m_arySound[SOUND_ITEM_LIFE]		= m_Sound.Load("../../data/bgPangPang/item_life.wav", false);
	m_arySound[SOUND_LIFE_MINUS]	= m_Sound.Load("../../data/bgPangPang/life_minus.wav", false);
	m_arySound[SOUND_DIE]			= m_Sound.Load("../../data/bgPangPang/die.wav", false);

	m_Sound.SetLoop(SOUND_BGM_MAIN);
	m_Sound.SetLoop(SOUND_BGM_BACK1);
	m_Sound.SetLoop(SOUND_BGM_BACK2);
	m_Sound.SetLoop(SOUND_BGM_BACK3);
	m_Sound.SetLoop(SOUND_BGM_BACK4);

	// 개수대로 로드하는 문제로 인해서 메인에서 로드...
	I_FrameMgr.Add(L"../../data/bgPangPang/object.txt");
	I_FrameMgr.Add(L"../../data/bgPangPang/bullet.txt");
	I_FrameMgr.Add(L"../../data/bgPangPang/effect.txt");
	I_FrameMgr.Add(L"../../data/bgPangPang/item.txt");

	I_FrameMgr.Add(L"../../data/bgPangPang/menu.txt");

	m_Gameover.Init();
	m_Ground.Init();
	m_Hero.Init();
	m_Font.Init();
	m_UI.Init();
	m_UI.SetDC(g_hOffScreenDC);
	m_UI.SetBitmap(L"item.bmp");
	m_UI.SetSprite(L"Life");

	int i;
	for (i = 0; i < MAX_BULLET; i++)
		m_Bullet[i].Init();
	for (i = 0; i < MAX_OBJECT; i++)
		m_Object[i].Init();
	for (i = 0; i < MAX_EFFECT; i++)
		m_Effect[i].Init();
	for (i = 0; i < MAX_ITEM; i++)
		m_Item[i].Init();

	m_GameState = STATE_MAIN;
	m_Sound.Play(m_arySound[SOUND_BGM_MAIN], true);

	return true;

}

bool GameMain::Frame()
{
	switch (m_GameState)
	{
	case STATE_SINGLE:
		SingleFrame();
		break;
	case STATE_MAIN:
		MainFrame();
		break;
	case STATE_NETWORK:
		NetworkFrame();
		break;
	case STATE_EXIT:
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
	case STATE_SINGLE:
		SingleRender();
		break;
	case STATE_MAIN:
		MainRender();
		break;
	case STATE_NETWORK:
		NetworkRender();
		break;
	}
	return true;
}

bool GameMain::Release()
{
	m_Ground.Release();
	m_Hero.Release();
	m_Font.Release();
	m_UI.Release();

	int i;
	for (i = 0; i < MAX_BULLET; i++)
		m_Bullet[i].Release();
	for (i = 0; i < MAX_OBJECT; i++)
		m_Object[i].Release();
	for (i = 0; i < MAX_EFFECT; i++)
		m_Effect[i].Release();
	for (i = 0; i < MAX_ITEM; i++)
		m_Item[i].Release();

	m_Sound.Release();

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

int WINAPI wWinMain(HINSTANCE hInstatnce, HINSTANCE hPrevInstatnce, LPWSTR lpCmdLine, int nCmdShow)
{
	GameMain win;
	if (win.SetWindow(hInstatnce) == true)
	{
		win.CenterWindow();
		win.Run();
	}
	return 0;
}
