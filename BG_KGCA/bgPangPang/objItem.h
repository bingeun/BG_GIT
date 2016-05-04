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
	bool	m_bLife;

public:
	bool	Init();
	bool	Frame();
	bool	Render();
	bool	Release();

public:
	objItem();
	virtual ~objItem();
};

