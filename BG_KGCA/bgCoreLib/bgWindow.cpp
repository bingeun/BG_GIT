#include "bgWindow.h"

bgWindow*	g_pWindow;

// 윈도우 관련 전역변수
HWND		g_hWnd;
HINSTANCE	g_hInstance;
RECT		g_rtWindow;

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

bool bgWindow::SetWindow(HINSTANCE hInstance, TCHAR* titleName, int iX, int iY, int iWidth, int iHeight)
{
	m_hInstance = hInstance;

	if (m_iWidth == 0 && m_iHeight == 0)
	{
		m_iWidth = iWidth;
		m_iHeight = iHeight;
	}

	// 1. 윈도우 클래스 객체 등록
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
	wc.cbClsExtra = 0; // 윈도우 클래스에서 사용하려는 여분의 메모리 크기
	wc.cbWndExtra = 0; // 윈도우에서 사용하려는 여분의 메모리 크기
	wc.lpszMenuName = NULL;
	wc.lpfnWndProc = WndProc;
	if (RegisterClassEx(&wc) == false)
	{
		return false;
	}

	// 클라이언트 영역을 정확하게 설정하기 위해 계산
	RECT rt = { 0, 0, m_iWidth, m_iHeight };
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, FALSE);

	// 2. 등록된 객체 사용하여 윈도우 생성
	m_hWnd = CreateWindowEx( // WS_EX_APPWINDOW 기본, WS_EX_TOPMOST 항상 위에
		WS_EX_APPWINDOW, L"BG", L"BG First!", WS_OVERLAPPEDWINDOW, // WS_OVERLAPPEDWINDOW, WS_POPUPWINDOW, WS_OVERLAPPED
		iX, iY, rt.right - rt.left, rt.bottom - rt.top, NULL, NULL, hInstance, NULL);

	// 3. 윈도우 보이기
	if (m_hWnd != NULL)
	{
		ShowWindow(m_hWnd, SW_SHOW);
	}

	GetWindowRect(m_hWnd, &m_rtWindow);
	GetClientRect(m_hWnd, &m_rtClient);

	// 전역변수 설정
	g_hWnd = m_hWnd;
	g_hInstance = m_hInstance;
	g_rtWindow = m_rtWindow;
	return true;
}

bool bgWindow::Run()
{
	MSG msg;

	GameInit();
	ZeroMemory(&msg, sizeof(msg));
	while (msg.message != WM_QUIT)
	{
		// 메세지 큐에서 원시 메세지 1개 가져오기
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg); // 원시 메세지 해석
			DispatchMessage(&msg); // 해석된 메세지를 프로시저에 전달
			MsgEvent(msg);
		}
		else
		{
			GameRun();
		}
	}
	GameRelease();
	return true;
}

bool bgWindow::Release()
{
	return true;
}

void bgWindow::SetRect(int iWidth, int iHeight)
{
	m_iWidth = iWidth;
	m_iHeight = iHeight;
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

bool bgWindow::ResizeClient(UINT iWidth, UINT iHeight)
{
	GetClientRect(m_hWnd, &m_rtWindow);
	g_rtWindow = m_rtWindow;
	return true;
}

bgWindow::bgWindow()
{
	g_pWindow = this;
}

bgWindow::~bgWindow()
{
}
