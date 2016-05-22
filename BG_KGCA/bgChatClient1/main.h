#pragma once
#include "bgCore.h"
#include "bgAsyncSelect.h"

#define SERVER_IP	"192.168.0.8"
#define SERVER_PORT	(10000)

class bgMain : public bgCore
{
public:
	bgAsyncSelect	m_Network;
	HWND		m_hEdit;
	HWND		m_hButton;
	HWND		m_hList;

public:
	bool		GameRender() { return true; }
	bool		Init();
	bool		Frame();
	bool		Release();
	LRESULT		MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	void		MsgEvent(MSG msg);

public:
	bgMain();
	virtual ~bgMain();
};
