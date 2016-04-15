#include "bgObject.h"


bool bgObject::Load(HDC hScreenDC, HDC hOffScreenDC, TCHAR * pFileName)
{
	m_hScreenDC = hScreenDC;
	m_hOffScreenDC = hOffScreenDC;
	m_hBitmap = (HBITMAP)LoadImage(g_hInstance, pFileName, IMAGE_BITMAP, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE);
	GetObject(m_hBitmap, sizeof(BITMAP), &m_hBitInfo);
	m_hMemDC = CreateCompatibleDC(hScreenDC);
	m_hOldBitmap = (HBITMAP)SelectObject(m_hMemDC, m_hBitmap);
	return true;
}

void bgObject::Left()
{
	m_iX -= g_fSecondPerFrame * m_fSpeed;
}

void bgObject::Right()
{
	m_iX += g_fSecondPerFrame * m_fSpeed;
}

void bgObject::Up()
{
	m_iY -= g_fSecondPerFrame * m_fSpeed;
}

void bgObject::Down()
{
	m_iY += g_fSecondPerFrame * m_fSpeed;
}

bool bgObject::Draw()
{
	StretchBlt(m_Bitmap.m_hOffScreenDC, m_fX, m_fY, 800, 600, m_Bitmap.m_hMemDC,
		m_Bitmap.m_bmWidth, m_Bitmap.m_bmHeight, m_Bitmap.m_bmWidth, m_Bitmap.m_bmHeight, SRCCOPY);
	return true;
}

void bgObject::SetPos(int iX, int iY)
{
	m_iX = iX;
	m_iY = iY;
}

void bgObject::SetSpeed(float fSpeed)
{
	m_fSpeed += fSpeed;
}

bool bgObject::Init()
{
	m_fSpeed = 30.0f;
	m_iX = 100;
	m_iY = 100;
	return true;
}

bool bgObject::Frame()
{
	return true;
}

bool bgObject::Render()
{
	// 1:1 출력
	//BitBlt(m_hOffScreenDC, 0, 0, m_hBitInfo.bmWidth, m_hBitInfo.bmHeight, m_hMemDC, 0, 0, SRCCOPY);
	// 확대 ~ 축소 출력
	StretchBlt(m_hOffScreenDC, 0, 0, 800, 600, m_hMemDC, 0, 0, m_hBitInfo.bmWidth, m_hBitInfo.bmHeight, SRCCOPY);
	return true;
}

bool bgObject::Release()
{
	SelectObject(m_hMemDC, m_hOldBitmap);
	ReleaseDC(g_hWnd, m_hMemDC);
	return true;
}

bgObject::bgObject()
{
}


bgObject::~bgObject()
{
}
