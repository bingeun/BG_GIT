#pragma once
#include "bgStd.h"
#include "bgSys.h"
#include "bgObject.h"

#define BULLET_SPEED (400.0f)

enum BULLET_TYPE
{
	BULLET_SINGLE = 0,
	BULLET_DOUBLE,
	BULLET_FIXED,
	BULLET_GUN,
	BULLET_GUN_LEFT,
	BULLET_GUN_RIGHT,
};

class objBullet : public bgObject
{
public:
	BULLET_TYPE	m_BulletType;
	float	m_fPosYHead; // BULLET_GUN Á¦¿Ü

public:
	

	bool	Init();
	bool	Frame();
	bool	Render();
	bool	Release();

public:
	objBullet();
	virtual ~objBullet();
};

