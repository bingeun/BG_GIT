#include "bgCore.h"

// 화면 관련 전역변수
HDC		g_hScreenDC;
HDC		g_hOffScreenDC;

bool bgCore::PreRender()
{
	SelectObject(m_hOffScreenDC, m_hBrush);
	PatBlt(m_hOffScreenDC, 0, 0, m_rtWindow.right, m_rtWindow.bottom, PATCOPY);
	return true;
}

bool bgCore::PostRender()
{
	BitBlt(m_hScreenDC, m_rtWindow.left, m_rtWindow.top, m_rtWindow.right, m_rtWindow.bottom, m_hOffScreenDC, 0, 0, SRCCOPY);
	return true;
}

bool bgCore::DrawDebug()
{
	return true;
}

bool bgCore::DrawDebug(TCHAR * pString, int iX, int iY)
{
#ifdef _DEBUG
	if (m_hOffScreenDC != NULL)
	{
		SetBkColor(m_hOffScreenDC, RGB(255, 0, 0));
		SetTextColor(m_hOffScreenDC, RGB(0, 0, 255));
		SetBkMode(m_hOffScreenDC, TRANSPARENT);
		SetTextAlign(m_hOffScreenDC, TA_LEFT);

		TextOut(m_hOffScreenDC, iX, iY, pString, wcslen(pString));
	}
#endif // _DEBUG
	return true;
}

bool bgCore::GameRun()
{
	GameFrame();
	GameRender();
	return true;
}

bool bgCore::GameInit()
{
	m_Timer.Init();
	m_Input.Init();

	// 전면 버퍼, 후면 버퍼 & 후면 비트맵 생성
	m_hScreenDC = GetDC(m_hWnd);
	m_hOffScreenDC = CreateCompatibleDC(m_hScreenDC);
	m_hOffScreenBitmap = CreateCompatibleBitmap(m_hScreenDC, m_rtWindow.right, m_rtWindow.bottom);
	m_hScreenBitmap = (HBITMAP)SelectObject(m_hOffScreenDC, m_hOffScreenBitmap);

	// 배경색상 및 폰트 설정
	COLORREF ColorBack = RGB(0xFF, 0xFF, 0xFF);
	m_hBrush = CreateSolidBrush(ColorBack);
	m_hOldBrush = (HBRUSH)SelectObject(m_hOffScreenDC, m_hBrush);
	m_hFont = CreateFont(12, 0, 0, FW_BOLD, 0, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1, VARIABLE_PITCH | FF_ROMAN, _T("돋움"));
	m_hOldFont = (HFONT)SelectObject(m_hOffScreenDC, m_hFont);

	// 전역변수 설정
	g_hScreenDC = m_hScreenDC;
	g_hOffScreenDC = m_hOffScreenDC;

	Init();
	return true;
}

bool bgCore::GameFrame()
{
	m_Timer.Frame();
	m_Input.Frame();
	PreFrame();
	{
		Frame();
	}
	PostFrame();
	return true;
}

bool bgCore::GameRender()
{
	PreRender();
	{
		Render();
		m_Timer.Render();
		m_Input.Render();
		DrawDebug();
	}
	PostRender();
	return true;
}

bool bgCore::GameRelease()
{
	Release();

	SelectObject(m_hOffScreenDC, m_hOldBrush);
	DeleteObject(m_hBrush);
	SelectObject(m_hOffScreenDC, m_hOldFont);
	DeleteObject(m_hFont);
	SelectObject(m_hOffScreenDC, m_hScreenBitmap);

	ReleaseDC(m_hWnd, m_hScreenDC);

	m_Timer.Release();
	m_Input.Release();
	return true;
}

void bgCore::MsgEvent(MSG msg)
{
	m_Input.MsgEvent(msg);
}

bgCore::bgCore()
{
}


bgCore::~bgCore()
{
}
