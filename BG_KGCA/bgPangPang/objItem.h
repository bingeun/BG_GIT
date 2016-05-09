#pragma once
#include "bgStd.h"
#include "bgSys.h"
#include "bgObject.h"

#define ITEM_W		(45)
#define ITEM_H		(30)
#define LIFE_X		(25)
#define LIFE_Y		(550)

#define MAX_ITEM	(30)
#define MAX_LIFE	(5)
#define ITEM_DROP_SPEED		(150.0f)
#define LIFETIME_ITEM		(10.0f)

enum ITEM_TYPE
{
	ITEM_WEAPON_SINGLE = 0,
	ITEM_WEAPON_DOUBLE,
	ITEM_WEAPON_FIXED,
	ITEM_WEAPON_GUN,
	ITEM_FOOD1,
	ITEM_FOOD2,
	ITEM_FOOD3,
	ITEM_FOOD4,
	ITEM_LIFE,
	ITEM_CLOCK,
	ITEM_SHIELD,
};

class objItem : public bgObject
{
public:
	ITEM_TYPE	m_ItemType;
	bool	m_bLife;
	float	m_fLifeTime;
	float	m_fPosA; // X 증가값
	float	m_fPosB; // Y 증가값

public:
	bool	Init();
	bool	Frame();
	bool	Render();
	bool	Release();

public:
	objItem();
	virtual ~objItem();
};

