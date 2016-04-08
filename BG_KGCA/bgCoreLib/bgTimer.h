#pragma once
#include "bgBase.h"

class bgTimer : public bgBase
{
public:
	int		m_iFPS;
	float	m_fSecondPerFrame;
	float	m_fAccumulation;

public:
	TCHAR	m_csBuffer[MAX_PATH];
	DWORD	m_dwBeforeTick;
	float	m_fFrameTime;
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

