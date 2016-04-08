#pragma once
#include "bgTimer.h"
#include "bgWindow.h"

class bgCore : public bgWindow
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

