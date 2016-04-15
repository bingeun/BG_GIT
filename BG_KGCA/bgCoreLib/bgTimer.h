#pragma once
#include "bgBase.h"

class bgTimer : public bgBase, public bgSingleton<bgTimer>
{
public:
	TCHAR	m_csBuffer[MAX_PATH];
	int		m_iFPS;
	float	m_fSecondPerFrame;
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
};

