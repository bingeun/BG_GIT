#pragma once
#include "bgStd.h"
#include "bgSys.h"
#include "bgObject.h"

#define HERO_SPEED (200.0f)

class objHero : public bgObject
{
public:
	bool	m_isLeft;

public:
	void	Left();
	void	Right();
	void	Up();
	void	Down();
	void	SpeedUp(float fSpeedUp = 1.0f);
	void	SpeedDown(float fSpeedDown = 1.0f);
	void	DirectionLeft(float fDirection = 45.0f); // Left => +45.0f
	void	DirectionRight(float fDirection = 315.0f); // Right => -45.0f
	void	SetDirection(float fDirection) { m_fDirection = fDirection; }

	bool	Init();
	bool	Frame();
	bool	Render();
	bool	Release();

public:
	objHero();
	virtual ~objHero();
};

