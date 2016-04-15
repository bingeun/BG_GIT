#include "bgWindow.h"


LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
	{
		PostQuitMessage(0); // �޼��� ť ���� �ڿ� WM_QUIT �� �߰�
	}
	break;

	case WM_SIZE:
	{
		UINT iWidth = LOWORD(lParam);
		UINT iHeight = HIWORD(lParam);
		TCHAR str[MAX_PATH] = { 0, };
		_stprintf_s(str, L"%d, %d\n", iWidth, iHeight);
		OutputDebugString(str);
	}
	break;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

void bgWindow::SetRect(int iWidth, int iHeight)
{
	m_iWidth = iWidth;
	m_iHeight = iHeight;
}

bool bgWindow::SetWindow(HINSTANCE hInstance, TCHAR* titleName, int iX, int iY, int iWidth, int iHeight)
{
	m_hInstance = hInstance;
	g_hInstance = hInstance;
	if (m_iWidth == 0 && m_iHeight == 0)
	{
		m_iWidth = iWidth;
		m_iHeight = iHeight;
	}

	// 1. ������ Ŭ���� ��ü ���
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.lpszClassName = L"BG";
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_QUESTION);
	wc.hIconSm = LoadIcon(NULL, IDI_WARNING);
	wc.hCursor = LoadCursor(NULL, IDC_CROSS);
	wc.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
	wc.cbClsExtra = 0; // ������ Ŭ�������� ����Ϸ��� ������ �޸� ũ��
	wc.cbWndExtra = 0; // �����쿡�� ����Ϸ��� ������ �޸� ũ��
	wc.lpszMenuName = NULL;
	wc.lpfnWndProc = WndProc;
	if (RegisterClassEx(&wc) == false)
	{
		return false;
	}

	// Ŭ���̾�Ʈ ������ ��Ȯ�ϰ� �����ϱ� ���� ���
	RECT rt = { 0, 0, m_iWidth, m_iHeight };
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, FALSE);

	// 2. ��ϵ� ��ü ����Ͽ� ������ ����
	m_hWnd = CreateWindowEx( // WS_EX_APPWINDOW �⺻, WS_EX_TOPMOST �׻� ����
		WS_EX_APPWINDOW, L"BG", L"BG First!", WS_POPUPWINDOW, // WS_OVERLAPPEDWINDOW, WS_POPUPWINDOW, WS_OVERLAPPED
		(1920 - 800) / 2, (1080 - 600) / 2, rt.right - rt.left, rt.bottom - rt.top, NULL, NULL, hInstance, NULL);

	// 3. ������ ���̱�
	if (m_hWnd != NULL)
	{
		ShowWindow(m_hWnd, SW_SHOW);
	}
	g_hWnd = m_hWnd;

	GetWindowRect(m_hWnd, &m_rtWindow);
	GetClientRect(m_hWnd, &m_rtClient);

	return true;
}

void bgWindow::CenterWindow()
{
	int iScreenWidth = GetSystemMetrics(SM_CXSCREEN);
	int iScreenHeight = GetSystemMetrics(SM_CYSCREEN);
	int x = (iScreenWidth - (m_rtWindow.right - m_rtWindow.left)) / 2;
	int y = (iScreenHeight - (m_rtWindow.bottom - m_rtWindow.top)) / 2;
	int w = m_rtWindow.right - m_rtWindow.left;
	int h = m_rtWindow.bottom - m_rtWindow.top;

	MoveWindow(m_hWnd, x, y, w, h, true);
}

bgWindow::bgWindow()
{
}

bgWindow::~bgWindow()
{
}
