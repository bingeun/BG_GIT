#include "bgBitmap.h"


bool bgBitmap::Load(TCHAR* pszName)
{
	m_hBitmap = (HBITMAP)LoadImage(g_hInstance, pszName, IMAGE_BITMAP, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE);
	if (m_hBitmap == NULL)
		return false;

	// 파일경로를 요소별로 분리
	TCHAR Drive[MAX_PATH] = { 0, };
	TCHAR Dir[MAX_PATH] = { 0, };
	TCHAR Name[MAX_PATH] = { 0, };
	TCHAR Ext[MAX_PATH] = { 0, };
	_tsplitpath_s(pszName, Drive, Dir, Name, Ext);

	// [파일명.확장자] 형태로 멤버변수로 지정
	_stprintf_s(m_pszName, _T("%s%s"), Name, Ext);

	GetObject(m_hBitmap, sizeof(BITMAP), &m_BitmapInfo);
	m_hMemDC = CreateCompatibleDC(m_hScreenDC);
	m_hOldBitmap = (HBITMAP)SelectObject(m_hMemDC, m_hBitmap);
	
	return true;
}

HBITMAP bgBitmap::GetRotationBitmap(HDC hdc, RECT& rect, int iWidth, int iHeight, float fAngle = 0)
{
	// 새로운 비트맵 생성 및 초기화
	HDC		hScreenDC = CreateCompatibleDC(m_hScreenDC);
	HBITMAP	hBitmapResult = CreateCompatibleBitmap(m_hScreenDC, iWidth, iHeight);
	HBITMAP hBitmapOld = (HBITMAP)SelectObject(hScreenDC, hBitmapResult);

	COLORREF rgbBack = RGB(0xFF, 0xFF, 0xFF);
	HBRUSH   hBrushBack = CreateSolidBrush(rgbBack);
	HBRUSH   hBrushOld = (HBRUSH)SelectObject(hScreenDC, hBrushBack);
	PatBlt(hScreenDC, 0, 0, iWidth, iHeight, PATCOPY);
	DeleteObject(SelectObject(hScreenDC, hBrushOld));

	// 회전
	float fRadian = RadianToDegree(fAngle);
	float fSin = sin(fRadian);
	float fCos = cos(fRadian);
	XFORM xForm;
	xForm.eM11 = fCos;
	xForm.eM12 = -fSin;
	xForm.eM21 = fSin;
	xForm.eM22 = fCos;
	xForm.eDx = iWidth / 2;
	xForm.eDy = iHeight / 2;
	int iGraphicsModeOld = SetGraphicsMode(hScreenDC, GM_ADVANCED);
	SetWorldTransform(hScreenDC, &xForm);

	// 출력~!!!
	BitBlt(hScreenDC, -(rect.right / 2.0f), -(rect.bottom / 2.0f), rect.right, rect.bottom, hdc, rect.left, rect.top, SRCCOPY);

	// 원상복귀
	SelectObject(hScreenDC, hBitmapOld);
	DeleteObject(hScreenDC);

	xForm.eM11 = 1;
	xForm.eM12 = 0;
	xForm.eM21 = 0;
	xForm.eM22 = 1;
	xForm.eDx = 0;
	xForm.eDy = 0;
	SetWorldTransform(hScreenDC, &xForm);
	SetGraphicsMode(hScreenDC, iGraphicsModeOld);

	return hBitmapResult;
}

bool bgBitmap::Draw(HDC hdc, POINT pos, RECT rect, DWORD mode = SRCCOPY, float fAngle = 0)
{
	switch ()
	{
	case :
		break;
	}
	return true;
}


HBITMAP GameMain::GetRotationBitmap(HDC hdc, float fAngle, int iWidth, int iHeight)
{
	HDC BitmapDC = CreateCompatibleDC(g_hScreenDC);
	HBITMAP bitmap = CreateCompatibleBitmap(g_hScreenDC, iWidth, iHeight);
	HBITMAP oldBitmap = SelectObject(BitmapDC, bitmap);
	HBRUSH back = CreateSolidBrush(RGB(0xFF, 0xFF, 0xFF));
	HBRUSH oldBrush = (HBRUSH)SelectObject(BitmapDC, back);
	PatBlt(BitmapDC, 0, 0, iWidth, iHeight, PATCOPY);
	DeleteObject(SelectObject(BitmapDC, oldBrush));

	float fRad = RadianToDegree(fAngle);
	float fSin = sin(fAngle);
	float fCos = cos(fAngle);
	XFORM xForm;
	xForm.eM11 = fCos;
	xForm.eM12 = -fSin;
	xForm.eM21 = fSin;
	xForm.eM22 = fCos;
	xForm.eDx = iWidth / 2;
	xForm.eDy = iHeight / 2;
	SetWorldTransform(BitmapDC, &xForm); // 행렬의 곱셈 담당.

	BitBlt(...);
	DeleteObject(BitmapDC);
	SetGraphicsMode(hdc, iOldMode);
	return bitmap;
}

void bgBitmap::DrawRotate(float fAngle)
{
	RECT rt;
	rt.left = 91;
	rt.top = 1;
	rt.right = 41;
	rt.bottom = 60;
	int iOffWidth = rt.right;
	int iOffHeight = rt.bottom;
	if (iOffWidth > iOffHeight)
		iOffHeight = iOffWidth;
	else
		iOffWidth = iOffHeight;
	
	HBITMAP hMaskBitmap = GetRotationBitmap(m_MaskBitmap.m_hMemDC, fAngle, iOffWidth, iOffHeight);
	HBITMAP hColorBitmap = GetRotationBitmap(m_ColorBitmap.m_hMemDC, fAngle, iOffWidth, iOffHeight);

	HDC hMaskMemDC = CreateCompatibleDC(g_hScreenDC);
	HDC hColorMemDC = CreateCompatibleDC(g_hScreenDC);
	HBITMAP hOldMask = (HBITMAP)SelectObject(hMaskMemDC, hMaskBitmap);
	HBITMAP hOldColor = (HBITMAP)SelectObject(hColorMemDC, hColorBitmap);

	BitBlt();
	BitBlt();
	BitBlt();

	SelectObject(hMaskMemDC, hOldMask);
	SelectObject(hColorMemDC, hOldColor);
	DeleteDC(hMaskMemDC);
	DeleteDC(hColorMemDC);
	DeleteObject(hMaskBitmap);
	DeleteObject(hColorBitmap);





	HDC hdc;
	hdc = CreateCompatibleDC(m_hScreenDC);
	HBITMAP hBitmap = CreateCompatibleBitmap(m_hScreenDC, 100, 100);
	SelectObject(hdc, hBitmap);

	HBRUSH back = CreateSolidBrush(RGB(0xFF, 0xFF, 0xFF));
	SelectObject(hdc, back);
	PatBlt(hdc, 0, 0, 100, 100, PATCOPY);

	int OldMode = SetGraphicsMode(BitmapDC, GM_ADVANCED); //hdc, GM_ADVANCED);
	float fRad = RadianToDegree(fAngle);
	float fSin = sin(fAngle);
	float fCos = cos(fAngle);
	XFORM xForm;
	xForm.eM11 = fCos;
	xForm.eM12 = -fSin;
	xForm.eM21 = fSin;
	xForm.eM22 = fCos;
	xForm.eDx = 0;
	xForm.eDy = 0;
	SetWorldTransform(hdc, &xForm); // 행렬의 곱셈 담당.

	BitBlt(hdc, 0, 0, 100, 100, 원본DC, 0, 0, SRCCOPY);

	SetGraphicsMode(hdc, OldMode);
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
	Draw();
	return true;
}

bool bgBitmap::Release()
{
	SelectObject(m_hMemDC, m_hOldBitmap);
	//ReleaseDC(g_hWnd, m_hMemDC);
	ReleaseDC(g_hWnd, m_hMemDC);
	return true;
}

bgBitmap::bgBitmap()
{
	m_iIndex = 0;
}


bgBitmap::~bgBitmap()
{
}
