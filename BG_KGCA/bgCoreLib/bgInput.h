#pragma once
#include "bgStd.h"

enum KeyState
{
	KEY_FREE = 0,
	KEY_PUSH,
	KEY_UP,
	KEY_HOLD,
};

class bgInput
{
public:
	DWORD	m_dwKeyState[256];
	DWORD	m_dwMouseState[3];
	POINT	m_MovePt;
	TCHAR	m_csBuffer[MAX_PATH];

public:
	DWORD	KeyCheck(DWORD dwKey);
	void	MsgEvent(MSG msg);

	bool	Init();
	bool	Frame();
	bool	Render();
	bool	Release();

public:
	bgInput();
	~bgInput();
};

