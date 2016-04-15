#include "bgTimer.h"
#include "bgSys.h"

int		g_iFPS;
float	g_fSecondPerFrame;
float	g_fAccumulation;

bool bgTimer::Init()
{
	m_dwBeforeTick = timeGetTime();
	ZeroMemory(m_csBuffer, sizeof(TCHAR)* MAX_PATH);
	return true;
}

bool bgTimer::Frame()
{
	DWORD dwCurrentTick = timeGetTime();
	DWORD dwElapseTick = dwCurrentTick - m_dwBeforeTick;

	g_fSecondPerFrame = dwElapseTick / 1000.0f;
	m_fSecondPerFrame = g_fSecondPerFrame;
	m_fAccumulation += m_fSecondPerFrame;
	m_fFrameTime += m_fSecondPerFrame;

	if (m_fFrameTime >= 1.0f)
	{
		m_iFPS = g_iFPS = m_dwFrameCounter;
		m_fFrameTime -= 1.0f;
		m_dwFrameCounter = 0;
	}
	m_dwFrameCounter++;
	m_dwBeforeTick = dwCurrentTick;
	return true;
}

bool bgTimer::Render()
{
#ifdef _DEBUG
	static float fTime = 0.0f;
	fTime += m_fSecondPerFrame;
	if (fTime >= 1.0f)
	{
		_stprintf_s(m_csBuffer, L"FPS = [%d] %10.4f %10.4f", m_iFPS, m_fSecondPerFrame, m_fAccumulation);
		fTime = 0.0f;
	}
	HDC hdc = GetDC(g_hWnd);
	//SetBkMode(hdc, TRANSPARENT); // 배경 투명하게
	TextOut(hdc, 0, 0, m_csBuffer, _tcslen(m_csBuffer));
	ReleaseDC(g_hWnd, hdc);
#endif // _DEBUG
	return true;
}

bool bgTimer::Release()
{
	return true;
}

bgTimer::bgTimer()
{
	m_iFPS = 0;
	m_dwFrameCounter = 0;
	m_fFrameTime = 0.0f;
	m_fAccumulation = 0.0f;
	m_fSecondPerFrame = 0.0f;
}


bgTimer::~bgTimer()
{
}
