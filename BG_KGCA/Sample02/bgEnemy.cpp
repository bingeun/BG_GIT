#include "bgSys.h"
#include "bgBitmap.h"


bool bgBitmap::Load(HDC hScreenDC, HDC hOffScreenDC, TCHAR * pFileName)
{
	m_hScreenDC = hScreenDC;
	m_hOffScreenDC = hOffScreenDC;
	m_hBitmap = (HBITMAP)LoadImage(g_hInstance, pFileName, IMAGE_BITMAP, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE);
	GetObject(m_hBitmap, sizeof(BITMAP), &m_hBitInfo);
	m_hMemDC = CreateCompatibleDC(hScreenDC);
	m_hOldBitmap = (HBITMAP)SelectObject(m_hMemDC, m_hBitmap);
	return true;
}

bool bgBitmap::Init()
{
	return true;
}

bool bgBitmap::Frame()
{
	return true;
}

bool bgBitmap::Render()
{
	// 1:1 출력
	//BitBlt(m_hOffScreenDC, 0, 0, m_hBitInfo.bmWidth, m_hBitInfo.bmHeight, m_hMemDC, 0, 0, SRCCOPY);
	// 확대 ~ 축소 출력
	StretchBlt(m_hOffScreenDC, 0, 0, 800, 600, m_hMemDC, 0, 0, m_hBitInfo.bmWidth, m_hBitInfo.bmHeight, SRCCOPY);
	return true;
}

bool bgBitmap::Release()
{
	SelectObject(m_hMemDC, m_hOldBitmap);
	ReleaseDC(g_hWnd, m_hMemDC);
	return true;
}

bgBitmap::bgBitmap()
{
}


bgBitmap::~bgBitmap()
{
}
