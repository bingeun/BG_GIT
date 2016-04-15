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
	virtual bool	PreRender();
	virtual bool	Render();
	virtual bool	PostRender();
	virtual bool	Release();

	virtual void	DebugString();
	virtual void	MsgEvent(MSG msg);

public:
	bool GameRun();
	bool GameInit();
	bool GameFrame();
	bool GameRender();
	bool GameRelease();

	bool Run();

public:
	bgCore();
	virtual ~bgCore();
};

