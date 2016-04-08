#include "bgWindow.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
	{
		PostQuitMessage(0); // 메세지 큐 제일 뒤에 WM_QUIT 를 추가
	}
	break;

	case WM_SIZE:
	{
	}
	break;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

bool bgWindow::SetWindow(HINSTANCE hInstance)
{
	// 1. 윈도우 클래스 객체 등록
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.lpszClassName = L"BG";
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_CROSS);
	wc.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.lpszMenuName = NULL;
	wc.lpfnWndProc = WndProc;
	if (RegisterClassEx(&wc) == false)
	{
		return false;
	}

	// 2. 등록된 객체 사용하여 윈도우 생성
	m_hWnd = CreateWindowEx( // WS_OVERLAPPEDWINDOW, WS_POPUPWINDOW, WS_OVERLAPPED
		WS_EX_APPWINDOW, L"BG", L"BG First!", WS_POPUPWINDOW,
		(1920 - 800) / 2, (1080 - 600) / 2, 800, 600, NULL, NULL, hInstance, NULL);

	// 3. 윈도우 보이기
	if (m_hWnd != NULL)
	{
		ShowWindow(m_hWnd, SW_SHOW);
	}
	GetWindowRect(m_hWnd, &m_rtWindow);
	GetClientRect(m_hWnd, &m_rtClient);

	return true;
}

bgWindow::bgWindow()
{
}

bgWindow::~bgWindow()
{
}
