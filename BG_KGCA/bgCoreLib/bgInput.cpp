#include "bgInput.h"
#include "bgSys.h"


void bgInput::MsgEvent(MSG msg)
{
	switch (msg.message)
	{
	case WM_LBUTTONDOWN:
	{
		GetCursorPos(&m_MousePos);
		ScreenToClient(g_hWnd, &m_MousePos);
		m_dwMouseState[0] = TRUE;
	}
	break;
	case WM_LBUTTONUP:
	{
		GetCursorPos(&m_MousePos);
		ScreenToClient(g_hWnd, &m_MousePos);
		m_dwMouseState[0] = FALSE;
	}
	break;
	case WM_RBUTTONDOWN:
	{
		GetCursorPos(&m_MousePos);
		ScreenToClient(g_hWnd, &m_MousePos);
		m_dwMouseState[1] = TRUE;
	}
	break;
	case WM_RBUTTONUP:
	{
		GetCursorPos(&m_MousePos);
		ScreenToClient(g_hWnd, &m_MousePos);
		m_dwMouseState[1] = FALSE;
	}
	break;
	case WM_MBUTTONDOWN:
	{
		GetCursorPos(&m_MousePos);
		ScreenToClient(g_hWnd, &m_MousePos);
		m_dwMouseState[2] = TRUE;
	}
	break;
	case WM_MBUTTONUP:
	{
		GetCursorPos(&m_MousePos);
		ScreenToClient(g_hWnd, &m_MousePos);
		m_dwMouseState[2] = FALSE;
	}
	break;
	}
}

DWORD bgInput::KeyCheck(DWORD dwKey)
{
	SHORT sKey = GetAsyncKeyState(dwKey);

	// 현재 눌림 상태
	if (sKey & 0x8000)
	{
		// 이전 안눌림 상태 = 누르는 순간
		if (m_dwKeyState[dwKey] == KEY_FREE)
		{
			m_dwKeyState[dwKey] = KEY_PUSH;
			m_fTimeKeyPush[dwKey] = g_fAccumulation + m_fTimeKeyFirstDelay;
		}
		// 이전 눌림 상태 = 지속적으로 누름
		else
		{
			m_dwKeyState[dwKey] = KEY_HOLD;
		}
	}
	// 현재 안눌림 상태
	else
	{
		// 이전 눌림 상태 = 떼는 순간
		if (m_dwKeyState[dwKey] == KEY_PUSH || m_dwKeyState[dwKey] == KEY_HOLD)
		{
			m_dwKeyState[dwKey] = KEY_UP;
		}
		// 이전 안눌림 상태 = 계속 안눌림
		else
		{
			m_dwKeyState[dwKey] = KEY_FREE;
		}
	}
	return m_dwKeyState[dwKey];
}

void bgInput::SetKeyDelay(float fTimeKeyFirstDelay, float fTimeKeyRepeatDelay)
{
	m_fTimeKeyFirstDelay = fTimeKeyFirstDelay;
	m_fTimeKeyRepeatDelay = fTimeKeyRepeatDelay;
}

bool bgInput::IsKeyHoldRepeat(DWORD dwKey)
{
	if (m_dwKeyState[dwKey] == KEY_FREE || m_dwKeyState[dwKey] == KEY_UP)
	{
		m_fTimeKeyPush[dwKey] = g_fAccumulation;
		return false;
	}

	if (g_fAccumulation - m_fTimeKeyPush[dwKey] >= m_fTimeKeyRepeatDelay)
	{
		m_fTimeKeyPush[dwKey] = g_fAccumulation;
		return true;
	}

	return false;
}

bool bgInput::Init()
{
	ZeroMemory(m_fTimeKeyPush, sizeof(DWORD) * MAX_KEYSTATE);
	ZeroMemory(m_dwKeyState, sizeof(DWORD) * MAX_KEYSTATE);
	ZeroMemory(m_dwMouseState, sizeof(DWORD) * 3);

	SetKeyDelay(0.3f, 0.075f);

	return true;
}

bool bgInput::Frame()
{
	GetCursorPos(&m_MousePos);
	ScreenToClient(g_hWnd, &m_MousePos);

	for (int iButton = 0; iButton < 3; iButton++)
	{
		if (m_dwMouseState[iButton] == KEY_PUSH)
		{
			m_dwMouseState[iButton] = KEY_HOLD;
		}
		if (m_dwMouseState[iButton] == KEY_UP)
		{
			m_dwMouseState[iButton] = KEY_FREE;
		}
	}
	return true;
}

bool bgInput::Render()
{
#ifdef _DEBUG
	_stprintf_s(m_csBuffer, L"Pos [%4d,%4d]", m_MousePos.x, m_MousePos.y);
	//SetBkMode(g_hOffScreenDC, TRANSPARENT); // 배경 투명하게
	//TextOut(g_hOffScreenDC, 2, 2 + 14 * 1, m_csBuffer, _tcslen(m_csBuffer));
#endif // _DEBUG
	return true;
}

bool bgInput::Release()
{
	return true;
}

bgInput::bgInput()
{
}


bgInput::~bgInput()
{
}
