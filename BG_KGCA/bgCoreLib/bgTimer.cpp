#include "bgTimer.h"



bool bgTimer::Init()
{
	m_fSecondPerFrame = 0.0f;
	m_iFPS = 0;
	m_dwBeforeTick = timeGetTime();
	m_fAccumulation = 0.0f;
	return true;
}

bool bgTimer::Frame()
{
	DWORD dwCurrentTick = timeGetTime();
	DWORD dwElapseTick = dwCurrentTick - m_dwBeforeTick;
	m_fSecondPerFrame = dwElapseTick / 1000.0f;
	m_fAccumulation += m_fSecondPerFrame;
	m_fFrameTime += m_fFrameTime;

	if (m_fFrameTime >= 1.0f)
	{
		m_iFPS = m_dwFrameCounter;
		m_fFrameTime -= 1.0f;
		m_dwFrameCounter = 0;
	}
	m_dwFrameCounter++;
	m_dwBeforeTick = dwCurrentTick;
	return true;
}

bool bgTimer::Render()
{
	static float;
	return true;
}

bool bgTimer::Release()
{
	return true;
}

bgTimer::bgTimer()
{
}


bgTimer::~bgTimer()
{
}
