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

	float	m_fTimer;
	float	m_fSecondPerRender;

public:
	bool	Init();
	bool	Frame();
	bool	Render();
	bool	Release();

public:
	bgSprite();
	virtual ~bgSprite();
};

