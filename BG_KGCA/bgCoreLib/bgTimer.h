#pragma once
#include "bgBase.h"

// 125 Byte = 1000밀리초(tick)의 비트열을 저장할 크기
// 1000/8 = 1바이트(8bit) 분의 1초(1000ms)
#define MSEC_PER_BYTE (1000/8)

class bgTimer : public bgBase, public bgSingleton<bgTimer>
{
public:
	TCHAR	m_csBuffer[MAX_PATH];
	int		m_iFPS;
	float	m_fSPF;
	float	m_fAccumulation;
	float	m_fFrameTime;
	DWORD	m_dwBeforeTick;
	DWORD	m_dwFrameCounter;

public:
	bool	Init();
	bool	Frame();
	bool	Render();
	bool	Release();

public:
	bgTimer();
	virtual ~bgTimer();


public:
	unsigned char m_bitArrayTick[MSEC_PER_BYTE];
};

