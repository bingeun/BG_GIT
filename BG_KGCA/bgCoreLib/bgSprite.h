#pragma once
#include "bgStd.h"
#include "bgSys.h"
#include "bgBitmap.h"

struct bgFrame
{
	bgBitmap*	pBitmap;
	RECT		rectSrc;
	float		fLifeTime;
};

class bgSprite
{
public:
	vector<bgFrame>	m_Frame;
	vector<bgFrame>::iterator m_iterFrame;
	wstring	m_szName;
	int		m_iNumLoop;

	int		m_iCountLoop;
	float	m_fTimer;

public:
	bool	Init();
	bool	Frame();
	bool	Render();
	bool	Release();

public:
	bgSprite();
	virtual ~bgSprite();
};

