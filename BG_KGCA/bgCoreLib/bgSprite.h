#pragma once
#include "bgStd.h"
#include "bgSys.h"
#include "bgFrame.h"


class bgSprite
{
public:
	bgFrame*	m_pFrame;
	vector<FRAME>::iterator m_iterFrame;
	int		m_iCountLoop;
	float	m_timeFrame;

public:
	bool	Init();
	bool	Frame();
	bool	Render();
	bool	Release();

public:
	bgSprite();
	virtual ~bgSprite();
};

