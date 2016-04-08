#pragma once
#include "bgCore.h"
#include "bgBase.h"

class bgSample : bgBase
{
public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();

public:
	bgSample();
	virtual ~bgSample();
};

