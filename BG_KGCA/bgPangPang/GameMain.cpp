#include "GameMain.h"

bool GameMain::Init()
{
	m_hScreenDC = GetDC(m_hWnd);
	m_hOffScreenDC = CreateCompatibleDC(m_hScreenDC);
	m_hOffScreenBitmap = CreateCompatibleBitmap(m_hScreenDC, CLIENT_W, CLIENT_H);
	SelectObject(m_hOffScreenDC, m_hOffScreenBitmap);

	I_SpriteMgr.Add(L"../../data/bgPangPang/menu.txt");
	I_SpriteMgr.Add(L"../../data/bgPangPang/font.txt");

	I_SpriteMgr.Add(L"../../data/bgPangPang/object.txt");
	I_SpriteMgr.Add(L"../../data/bgPangPang/item.txt");

	m_Ground.Init();
	m_Hero.Init();

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
	m_Bullet.clear();
	m_Hero.Release();

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
