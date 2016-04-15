#include "GameMain.h"
#include "bgSys.h"

bool GameMain::Init()
{
	m_hScreenDC = GetDC(m_hWnd);
	m_hOffScreenDC = CreateCompatibleDC(m_hScreenDC);
	m_hOffScreenBitmap = CreateCompatibleBitmap(m_hScreenDC, 800, 600);

	SelectObject(m_hOffScreenDC, m_hOffScreen);

	m_Background.Load(m_hOffScreenDC, m_hOffScreenDC, L"../../data/background.bmp");
	m_Hero.Load(m_hOffScreenDC, m_hOffScreenDC, L"../../data/hero.bmp");
	return true;
}

bool GameMain::Frame()
{
	if (m_Input.KeyCheck('A') == KEY_HOLD)
	{
		m_iX -= g_fSecondPerFrame * 100.0f;
	}
	if (m_Input.KeyCheck('D') == KEY_HOLD)
	{
		m_iX += g_fSecondPerFrame * 100.0f;
	}
	if (m_Input.KeyCheck('W') == KEY_HOLD)
	{
		m_iY -= g_fSecondPerFrame * 100.0f;
	}
	if (m_Input.KeyCheck('S') == KEY_HOLD)
	{
		m_iY += g_fSecondPerFrame * 100.0f;
	}
	return true;
}

bool GameMain::Render()
{
	COLORREF bkColor = RGB(255, 255, 255);
	HBRUSH hbrBack = CreateSolidBrush(bkColor);
	SelectObject(m_hOffScreenDC, hbrBack);
	PatBlt(m_hOffScreenDC, 0, 0, 800, 600, PATCOPY);

	m_Background.Render();
	m_Hero.Render();

	BitBlt(m_hScreenDC, 0, 0, 800, 600, m_hOffScreenDC, 0, 0, SRCCOPY);
	//BitBlt(m_hScreenDC, (800 - 512) / 2, (600 - 512) / 2, 512, 512, m_Background.m_hMemDC, 0, 0, SRCCOPY);
	//BitBlt(m_hScreenDC, (800 - 128) / 2 + (int)m_iX, (600 - 128) / 2 + (int)m_iY, 128, 128, m_Hero.m_hMemDC, 0, 0, SRCCOPY);
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
		win.Run();
	}
	return 0;
}
