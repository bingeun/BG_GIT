#pragma once
#include "bgStd.h"
#include "bgSys.h"
#include "bgObject.h"
#include "bgSpriteMgr.h"

class bgHero : public bgObject
{
public:
	bool	Init();
	bool	Frame();
	bool	Render();
	bool	Release();

public:
	bgHero();
	virtual ~bgHero();
};

