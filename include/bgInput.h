#pragma once
#include "bgStd.h"

enum KeyState
{
	KEY_FREE = 0,
	KEY_PUSH,
	KEY_UP,
	KEY_HOLD,
};

class bgInput : public bgSingleton<bgInput>
{
public:
	POINT	m_MousePos;
	DWORD	m_dwKeyState[256];
	DWORD	m_dwMouseState[3];
	TCHAR	m_csBuffer[MAX_PATH];

public:
	void	MsgEvent(MSG msg);
	DWORD	KeyCheck(DWORD dwKey);

	bool	Init();
	bool	Frame();
	bool	Render();
	bool	Release();

public:
	bgInput();
	virtual ~bgInput();
};

