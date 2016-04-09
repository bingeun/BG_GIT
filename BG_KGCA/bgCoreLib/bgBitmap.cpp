#include "bgSys.h"
#include "bgBitmap.h"


bool bgBitmap::Load(HDC hScreenDC, TCHAR * pFileName)
{
	m_hScreenDC = hScreenDC;
	BITMAP info;
	m_hBitmap = (HBITMAP)LoadImage(g_hInstance, pFileName, IMAGE_BITMAP, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE);
	GetObject(m_hBitmap, sizeof(BITMAP), &info);
	m_hMemDC = CreateCompatibleDC(hScreenDC);
	SelectObject(m_hMemDC, m_hBitmap);
	return true;
}

bgBitmap::bgBitmap()
{
}


bgBitmap::~bgBitmap()
{
}
