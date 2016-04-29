#pragma once
#include "bgStd.h"
#include "bgSys.h"
#include "bgObject.h"

#define MAX_EFFECT (50)

enum EFFECT_TYPE
{
	EFFECT_NUCLEAR = 0,
	EFFECT_FLOWER,
};

class objEffect : public bgObject
{
public:
	EFFECT_TYPE	m_EffectType;
	bool	m_bLife;

public:
	bool	Init();
	bool	Frame();
	bool	Render();
	bool	Release();

public:
	objEffect();
	virtual ~objEffect();
};

