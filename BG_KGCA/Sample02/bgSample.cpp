#include "bgSample.h"
#include "bgSys.h"

bool bgSample::Init()
{
	m_hScreenDC = GetDC(m_hWnd);
	m_Background.Load(m_hScreenDC, L"../../data/background.bmp");
	m_Hero.Load(m_hScreenDC, L"../../data/hero.bmp");
	return true;
}

bool bgSample::Frame()
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

bool bgSample::Render()
{
	BitBlt(m_hScreenDC, (800 - 512) / 2, (600 - 512) / 2, 512, 512, m_Background.m_hMemDC, 0, 0, SRCCOPY);
	BitBlt(m_hScreenDC, (800 - 128) / 2 + (int)m_iX, (600 - 128) / 2 + (int)m_iY, 128, 128, m_Hero.m_hMemDC, 0, 0, SRCCOPY);
	return true;
}

bool bgSample::Release()
{
	ReleaseDC(m_hWnd, m_hScreenDC);
	return true;
}

bgSample::bgSample()
{
	m_iX = 0;
	m_iY = 0;
}


bgSample::~bgSample()
{
}

int WINAPI wWinMain(HINSTANCE hInstatnce, HINSTANCE hPrevInstatnce, LPWSTR lpCmdLine, int nCmdShow)
{
	bgSample win;
	if (win.SetWindow(hInstatnce) == true)
	{
		win.Run();
	}
	return 0;
}
