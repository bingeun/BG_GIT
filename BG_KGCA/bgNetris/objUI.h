#pragma once
#include "bgStd.h"
#include "bgSys.h"
#include "bgObject.h"

class objUI : public bgObject
{
public:
	bool	Init();
	bool	Frame();
	bool	Render();
	bool	Release();

public:
	objUI();
	virtual ~objUI();
};
