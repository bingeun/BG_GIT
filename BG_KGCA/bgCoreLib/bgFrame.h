#pragma once
#include "bgStd.h"
#include "bgSys.h"
#include "bgBitmap.h"

struct FRAME
{
	bgBitmap*	pBitmap;
	POINT		posDest;
	RECT		rectSrc;
	float		fLifeTime;
};

class bgFrame
{
public:
	vector<FRAME>	m_vecFrame;
	wstring	m_szName;
	int		m_iTotalLoop;

public:
	void	Set(wstring szName, int iTotalLoop);
	void	Add(FRAME& frame);

public:
	bgFrame();
	virtual ~bgFrame();
};

