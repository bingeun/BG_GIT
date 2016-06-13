#pragma once
#include "bgStd.h"
#include "bgSys.h"

#define MAX_KEYSTATE	(256)

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
	float	m_fTimeKeyPush[MAX_KEYSTATE];
	DWORD	m_dwKeyState[MAX_KEYSTATE];
	DWORD	m_dwMouseState[3];
	TCHAR	m_csBuffer[MAX_PATH];
	float	m_fTimeKeyFirstDelay;
	float	m_fTimeKeyRepeatDelay;

public:
	void	MsgEvent(MSG msg);
	DWORD	KeyCheck(DWORD dwKey);
	void	SetKeyPush(DWORD dwKey) { m_fTimeKeyPush[dwKey] = g_fAccumulation; }
	float	GetKeyPush(DWORD dwKey) { return m_fTimeKeyPush[dwKey]; }

	void	SetKeyDelay(float fTimeKeyFirstDelay, float fTimeKeyRepeatDelay);
	bool	IsKeyHoldRepeat(DWORD dwKey);

	bool	Init();
	bool	Frame();
	bool	Render();
	bool	Release();

public:
	bgInput();
	virtual ~bgInput();
};

