#pragma once
#include "bgStd.h"
#include "bgSys.h"
#include "bgObject.h"

#define OBJECT_SPEED (50.0f)
#define MAX_OBJECT (256)

enum OBJECT_TYPE
{
	OBJECT_BALL = 0,
	OBJECT_POLYGON,
	OBJECT_BLOCK,
};

class objObject : public bgObject
{
public:
	OBJECT_TYPE	m_ObjectType;
	int		m_iObjectSize;
	bool	m_bLife;
	float	m_fPosA; // Ball = ball radius, Polygon = x+(a), Block = width
	float	m_fPosB; // Ball = jump height, Polygon = y+(a), Block = height

public:
	bool	Init();
	bool	Frame();
	bool	Render();
	bool	Release();

public:
	objObject();
	virtual ~objObject();
};

