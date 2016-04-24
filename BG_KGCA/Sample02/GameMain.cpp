#include "bgSys.h"
#include "GameMain.h"

bool GameMain::Init()
{
	m_hScreenDC = GetDC(m_hWnd);
	m_hOffScreenDC = CreateCompatibleDC(m_hScreenDC);
	m_hOffScreenBitmap = CreateCompatibleBitmap(m_hScreenDC, 800, 600);
	SelectObject(m_hOffScreenDC, m_hOffScreenBitmap);

	m_Hero.Init();
	return true;
}

bool GameMain::Frame()
{
	if (m_Input.KeyCheck('A') == KEY_HOLD)
	{
		m_Hero.Left();
		m_Hero.SetDirection(90.0f);
	}
	if (m_Input.KeyCheck('D') == KEY_HOLD)
	{
		m_Hero.Right();
		m_Hero.SetDirection(270.0f);
	}
	if (m_Input.KeyCheck('W') == KEY_HOLD)
	{
		m_Hero.Up();
		m_Hero.SetDirection(0.0f);
	}
	if (m_Input.KeyCheck('S') == KEY_HOLD)
	{
		m_Hero.Down();
		m_Hero.SetDirection(180.0f);
	}
	if (m_Input.KeyCheck('E') == KEY_HOLD)
	{
		m_Hero.SpeedUp();
	}
	if (m_Input.KeyCheck('Q') == KEY_HOLD)
	{
		m_Hero.SpeedDown();
	}

	m_Hero.Frame();
	return true;
}

bool GameMain::Render()
{
	m_Hero.Render();
	DrawDebug(L"Player Speed : %.2f", 2, 2 + 14 * 2);
	return true;
}

bool GameMain::Release()
{
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
