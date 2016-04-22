#include "bgTimer.h"
#include "bgSys.h"

// 타이머 관련 전역변수
int		g_iFPS;
float	g_fSPF;
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

	m_fSPF = dwElapseTick / 1000.0f;
	m_fAccumulation += m_fSPF;
	m_fFrameTime += m_fSPF;

	if (m_fFrameTime >= 1.0f)
	{
		m_iFPS = m_dwFrameCounter;
		m_fFrameTime -= 1.0f;
		m_dwFrameCounter = 0;
	}
	m_dwFrameCounter++;
	m_dwBeforeTick = dwCurrentTick;

	// 전역변수 설정
	g_iFPS = m_iFPS;
	g_fSPF = m_fSPF;
	g_fAccumulation = m_fAccumulation;
	return true;
}

bool bgTimer::Render()
{
#ifdef _DEBUG
	static float fTime = 0.0f;
	fTime += m_fSPF;
	if (fTime >= 1.0f)
	{
		_stprintf_s(m_csBuffer, L"FPS [%d], SPF [%.4f], Acc [%.4f]", m_iFPS, m_fSPF, m_fAccumulation);
		fTime = 0.0f;
	}
	SetBkMode(g_hOffScreenDC, TRANSPARENT); // 배경 투명하게
	TextOut(g_hOffScreenDC, 2, 2, m_csBuffer, _tcslen(m_csBuffer));
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
	m_fSPF = 0.0f;
	m_fAccumulation = 0.0f;
	m_fFrameTime = 0.0f;
	m_dwFrameCounter = 0;

	// 전역변수 설정
	g_iFPS = 0;
	g_fSPF = 0.0f;
	g_fAccumulation = 0.0f;
}


bgTimer::~bgTimer()
{
}
