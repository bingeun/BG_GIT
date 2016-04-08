#pragma once
#include "bgBase.h"

class bgTimer : bgBase
{
public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();

public:
	bgTimer();
	virtual ~bgTimer();
};

