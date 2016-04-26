#pragma once
#include "bgStd.h"
#include "bgSys.h"
#include "bgObject.h"

class objGround : public bgObject
{
public:


	bool	Init();
	bool	Frame();
	bool	Render();
	bool	Release();

public:
	objGround();
	virtual ~objGround();
};

