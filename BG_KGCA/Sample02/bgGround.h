#pragma once
#include "bgStd.h"
#include "bgSys.h"
#include "bgObject.h"

class bgGround : public bgObject
{
public:
	void	SetDirection(float fDirection) { m_fDirection = fDirection; }

	bool	Init();
	bool	Frame();
	bool	Render();
	bool	Release();

public:
	bgGround();
	virtual ~bgGround();
};

