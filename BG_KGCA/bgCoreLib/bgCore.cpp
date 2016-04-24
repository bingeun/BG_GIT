#include "bgCore.h"

// ȭ�� ���� ��������
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
#ifdef _DEBUG
#endif //_DEBUG
	return true;
}

bool bgCore::DrawDebug(TCHAR * pString, int iX, int iY)
{
#ifdef _DEBUG
	if (m_hOffScreenDC != NULL)
	{
		TextOut(m_hOffScreenDC, iX, iY, pString, wcslen(pString));
	}
#endif //_DEBUG
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
	// ���� ����, �ĸ� ���� & �ĸ� ��Ʈ�� ����
	m_hScreenDC = GetDC(m_hWnd);
	m_hOffScreenDC = CreateCompatibleDC(m_hScreenDC);
	m_hOffScreenBitmap = CreateCompatibleBitmap(m_hOffScreenDC, m_rtWindow.right, m_rtWindow.bottom);
	m_hScreenBitmap = (HBITMAP)SelectObject(m_hOffScreenDC, m_hOffScreenBitmap);

	// ������ �� ��Ʈ ����
	COLORREF ColorBack = RGB(0xDD, 0xDD, 0xFF);
	m_hBrush = CreateSolidBrush(ColorBack);
	m_hOldBrush = (HBRUSH)SelectObject(m_hOffScreenDC, m_hBrush);
	m_hFont = CreateFont(14, 0, 0, FW_BOLD, 0, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1, VARIABLE_PITCH | FF_ROMAN, _T("����ü"));
	m_hOldFont = (HFONT)SelectObject(m_hOffScreenDC, m_hFont);

	// Ÿ�̸� & �Է°��� Ŭ���� �ʱ�ȭ
	m_Timer.Init();
	m_Input.Init();

	// �������� ����
	g_hScreenDC = m_hScreenDC;
	g_hOffScreenDC = m_hOffScreenDC;

	// ���� ���ӷ��� �ʱ�ȭ�̹Ƿ� ���� �ļ��� ó��
	Init();

	return true;
}

bool bgCore::GameFrame()
{
	m_Timer.Frame();
	m_Input.Frame();
	PreFrame();
	{ // ��ó��
		Frame();
	} // ��ó��
	PostFrame();
	return true;
}

bool bgCore::GameRender()
{
	PreRender();
	{ // ��ó��
		Render();
		m_Timer.Render();
		m_Input.Render();
	} // ��ó��
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
