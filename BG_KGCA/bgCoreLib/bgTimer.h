#pragma once
#include "bgBase.h"

// 125 Byte = 1000�и���(tick)�� ��Ʈ���� ������ ũ��
// 1000/8 = 1����Ʈ(8bit) ���� 1��(1000ms)
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

