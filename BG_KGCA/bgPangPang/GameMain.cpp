#include "GameMain.h"

bool GameMain::Init()
{
	m_hScreenDC = GetDC(m_hWnd);
	m_hOffScreenDC = CreateCompatibleDC(m_hScreenDC);
	m_hOffScreenBitmap = CreateCompatibleBitmap(m_hScreenDC, CLIENT_W, CLIENT_H);
	SelectObject(m_hOffScreenDC, m_hOffScreenBitmap);

	// SOUND ##### 	m_Sound.Init();
	// SOUND ##### 	m_arySound[SOUND_BGM] = m_Sound.Load("../../data/bgPangPang/bgm.wav", false);
	// SOUND ##### 	m_arySound[SOUND_BALL_BURST] = m_Sound.Load("../../data/bgPangPang/ball_burst.wav", false);
	// SOUND ##### 	m_arySound[SOUND_BALL_DEVIDE] = m_Sound.Load("../../data/bgPangPang/ball_devide.wav", false);
	// SOUND ##### 	m_arySound[SOUND_LIFE_MINUS] = m_Sound.Load("../../data/bgPangPang/life_minus.wav", false);
	// SOUND ##### 	m_arySound[SOUND_DIE] = m_Sound.Load("../../data/bgPangPang/die.wav", false);

	I_SpriteMgr.Add(L"../../data/bgPangPang/menu.txt");
	I_SpriteMgr.Add(L"../../data/bgPangPang/font.txt");

	// 개수대로 로드하는 문제로 인해서 메인에서 로드...
	I_SpriteMgr.Add(L"../../data/bgPangPang/object.txt");
	I_SpriteMgr.Add(L"../../data/bgPangPang/bullet.txt");
	I_SpriteMgr.Add(L"../../data/bgPangPang/effect.txt");
	I_SpriteMgr.Add(L"../../data/bgPangPang/item.txt");

	m_Gameover.Init();
	m_Ground.Init();
	m_Hero.Init();

	int i;
	for (i = 0; i < MAX_BULLET; i++)
		m_Bullet[i].Init();
	for (i = 0; i < MAX_OBJECT; i++)
		m_Object[i].Init();
	for (i = 0; i < MAX_EFFECT; i++)
		m_Effect[i].Init();

	m_GameState = STATE_MAIN;

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
	// SOUND ##### 	m_Sound.Frame();
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
	for (int i = 0; i < MAX_BULLET; i++)
		m_Bullet[i].Release();
	for (int i = 0; i < MAX_OBJECT; i++)
		m_Object[i].Release();
	for (int i = 0; i < MAX_EFFECT; i++)
		m_Effect[i].Release();

	// SOUND ##### 	m_Sound.Release();

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
