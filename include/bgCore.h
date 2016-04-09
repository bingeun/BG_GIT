#pragma once
#include "bgTimer.h"
#include "bgInput.h"
#include "bgWindow.h"

class bgCore : public bgWindow
{
public:
	bgTimer		m_Timer;
	bgInput		m_Input;

public:
	virtual bool	Init();
	virtual bool	Frame();
	virtual bool	Render();
	virtual bool	Release();
	virtual void	MsgEvent(MSG msg);

public:
	bool Run();
	bool GameRun();
	bool GameInit();
	bool GameFrame();
	bool GameRender();
	bool GameRelease();

public:
	bgCore();
	virtual ~bgCore();
};

