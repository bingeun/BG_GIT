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
	if (sKey & 0x8000)
	{
		if (m_dwKeyState[dwKey] == KEY_FREE)
			m_dwKeyState[dwKey] = KEY_PUSH;
		else
			m_dwKeyState[dwKey] = KEY_HOLD;
	}
	else
	{
		if (m_dwKeyState[dwKey] == KEY_PUSH || m_dwKeyState[dwKey] == KEY_HOLD)
			m_dwKeyState[dwKey] = KEY_UP;
		else
			m_dwKeyState[dwKey] = KEY_FREE;
	}
	return m_dwKeyState[dwKey];
}

bool bgInput::Init()
{
	ZeroMemory(m_dwKeyState, sizeof(DWORD) * 256);
	ZeroMemory(m_dwMouseState, sizeof(DWORD) * 3);
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
	_stprintf_s(m_csBuffer, L"X = [%d], Y = [%d]", m_MousePos.x, m_MousePos.y);
	HDC hdc = GetDC(g_hWnd);
	//SetBkMode(hdc, TRANSPARENT); // 배경 투명하게
	TextOut(hdc, 0, 16, m_csBuffer, _tcslen(m_csBuffer));
	ReleaseDC(g_hWnd, hdc);
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
