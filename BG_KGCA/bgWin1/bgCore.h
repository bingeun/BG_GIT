#pragma once
#include "bgWindow.h"
#include "bgTimer.h"

class bgCore
{
public:
	bgTimer m_Timer;

public:
	bool GameInit();
	bool GameFrame();
	bool GameRender();
	bool GameRelease();
	bool GameRun();
	bool Run();

public:
	bgCore();
	virtual ~bgCore();
};

