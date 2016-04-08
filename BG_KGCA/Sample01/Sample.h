#pragma once
#include "bgCore.h"

class Sample : public bgCore
{
public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();

public:
	Sample();
	virtual ~Sample();
};

