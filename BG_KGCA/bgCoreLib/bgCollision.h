#pragma once
#include "bgStd.h"

struct bgSphere
{
	POINT pos;
	float radius;
};

class bgCollision
{
public:
	friend bool	RectInPoint(RECT& rectDest, POINT& posSrc);
	friend bool	RectInRect(RECT& rectDest, RECT& rectSrc);
	friend bool	SphereInSphere(bgSphere& sphDest, bgSphere& sphSrc);
	friend bool	SphereInSphere(RECT& rectDest, RECT& rectSrc);

public:
	bgCollision();
	virtual ~bgCollision();
};

