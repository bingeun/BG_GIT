#pragma once
#include "bgStd.h"
#include "bgSys.h"
#include "bgObject.h"

class objBack : public bgObject
{
public:
	bool	Init();
	bool	Frame();
	bool	Render();
	bool	Release();

public:
	objBack();
	virtual ~objBack();
};
