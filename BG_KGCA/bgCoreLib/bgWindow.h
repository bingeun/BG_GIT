#pragma once
#include "bgStd.h"
#include "bgSys.h"

class bgWindow
{
public:
	HINSTANCE	m_hInstance;
	HWND		m_hWnd;
	RECT		m_rtWindow;
	RECT		m_rtClient;
	int			m_iWidth;
	int			m_iHeight;
	bool		m_bActivate;

public:
	bool	SetWindow(HINSTANCE hInstance, TCHAR* titleName = L"BG Project", int iX = 0, int iY = 0, int iWidth = 800, int iHeight = 600);
	bool	Run();
	bool	Release();

	void	SetRect(int iWidth, int iHeight);
	void	CenterWindow();

	virtual bool	ResizeClient(UINT iWidth, UINT iHeight);

public:
	virtual bool	GameRun() { return true; }
	virtual bool	GameInit() { return true; }
	virtual bool	GameFrame() { return true; }
	virtual bool	GameRender() { return true; }
	virtual bool	GameRelease() { return true; }
	virtual void	MsgEvent(MSG msg) {}
	virtual LRESULT	MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) { return 0; }

public:
	bgWindow();
	virtual ~bgWindow();
};

