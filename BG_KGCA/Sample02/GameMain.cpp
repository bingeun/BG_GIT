#include "bgSys.h"
#include "GameMain.h"

bool GameMain::Init()
{
	m_hScreenDC = GetDC(m_hWnd);
	m_hOffScreenDC = CreateCompatibleDC(m_hScreenDC);
	m_hOffScreenBitmap = CreateCompatibleBitmap(m_hScreenDC, 800, 600);


	I_SpriteMgr.Add(L"../../data/airplane.txt");

	SelectObject(m_hOffScreenDC, m_hOffScreenBitmap);
	//m_Ground.Load(m_hScreenDC, m_hOffScreenDC, L"../../data/background.bmp");
	//m_Hero.Load(m_hScreenDC, m_hOffScreenDC, L"../../data/hero.bmp", L"../../data/hero_mask.bmp");
	//m_Enemy.Load(m_hScreenDC, m_hOffScreenDC, L"../../data/enemy.bmp", L"../../data/enemy_mask.bmp");
	//m_Hero.Load(m_hScreenDC, m_hOffScreenDC, L"../../data/airplane.bmp", L"../../data/airplane_mask.bmp");
	m_Hero.Init();
	return true;
}

bool GameMain::Frame()
{
	if (m_Input.KeyCheck('A') == KEY_HOLD)
	{
		m_fX -= g_fSPF * 100.0f;
	}
	if (m_Input.KeyCheck('D') == KEY_HOLD)
	{
		m_fX += g_fSPF * 100.0f;
	}
	if (m_Input.KeyCheck('W') == KEY_HOLD)
	{
		m_fY -= g_fSPF * 100.0f;
	}
	if (m_Input.KeyCheck('S') == KEY_HOLD)
	{
		m_fY += g_fSPF * 100.0f;
	}
	return true;
}

bool GameMain::Render()
{
	COLORREF colorBack = RGB(0xAA, 0xAA, 0xFF);
	HBRUSH hBrushBack = CreateSolidBrush(colorBack);
	SelectObject(m_hOffScreenDC, hBrushBack);
	PatBlt(m_hOffScreenDC, 0, 0, 800, 600, PATCOPY);

	//m_Ground.Render();
	//m_Hero.Render();
	//m_Enemy.Render();
	m_Hero.Render();

	DeleteObject(hBrushBack);
	return true;
}

bool GameMain::Release()
{
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
