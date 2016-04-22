#include "bgBitmap.h"


bool bgBitmap::Load(TCHAR* pszName, TCHAR* pszNameMask)
{
	// 파일경로를 분리할 요소들을 저장할 변수 선언
	TCHAR Drive[MAX_PATH] = { 0, };
	TCHAR Dir[MAX_PATH] = { 0, };
	TCHAR Name[MAX_PATH] = { 0, };
	TCHAR Ext[MAX_PATH] = { 0, };
	TCHAR NameExt[MAX_PATH] = { 0, };

	// 이미지 불러오기...
	m_hBitmap = (HBITMAP)LoadImage(g_hInstance, pszName, IMAGE_BITMAP, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE);
	if (m_hBitmap == NULL)
	{
		m_bMask = false;
		return false;
	}

	GetObject(m_hBitmap, sizeof(BITMAP), &m_BitmapInfo);
	m_hMemDC = CreateCompatibleDC(m_hScreenDC);
	m_hOldBitmap = (HBITMAP)SelectObject(m_hMemDC, m_hBitmap);

	// 파일경로를 요소별로 분리 후, [파일명.확장자] 형태로 멤버변수로 지정
	_tsplitpath_s(pszName, Drive, Dir, Name, Ext);
	Ext[4] = 0;
	memset(NameExt, 0, sizeof(TCHAR) * MAX_PATH);
	_stprintf_s(NameExt, _T("%s%s"), Name, Ext);
	m_szName = NameExt;

	// ====================== 마스크 파일을 지정했다면... ========================
	if (pszNameMask)
	{
		// 이미지 불러오기
		m_hBitmapMask = (HBITMAP)LoadImage(g_hInstance, pszNameMask, IMAGE_BITMAP, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE);
		if (m_hBitmapMask == NULL)
		{
			m_bMask = false;
			return true;
		}
		m_bMask = true;

		GetObject(m_hBitmapMask, sizeof(BITMAP), &m_BitmapInfoMask);
		m_hMemDCMask = CreateCompatibleDC(m_hScreenDC);
		SelectObject(m_hMemDCMask, m_hBitmapMask); // m_hOldBitmap = (HBITMAP)... 이미 old 저장했으므로 생략...

		// 파일경로를 요소별로 분리 후, [파일명.확장자] 형태로 멤버변수로 지정
		_tsplitpath_s(pszNameMask, Drive, Dir, Name, Ext);
		Ext[4] = 0;
		memset(NameExt, 0, sizeof(TCHAR) * MAX_PATH);
		_stprintf_s(NameExt, _T("%s%s"), Name, Ext);
		m_szNameMask = NameExt;
	}
	else
		m_bMask = false;

	return true;
}

bool bgBitmap::Load(DWORD dwBitmap)
{
	m_hBitmap = LoadBitmap(g_hInstance, MAKEINTRESOURCE(dwBitmap));
	GetObject(m_hBitmap, sizeof(BITMAP), &m_BitmapInfo);
	m_hMemDC = CreateCompatibleDC(m_hScreenDC);
	m_hOldBitmap = (HBITMAP)SelectObject(m_hMemDC, m_hBitmap);

	m_hBitmapMask = LoadBitmap(g_hInstance, MAKEINTRESOURCE(dwBitmap));
	GetObject(m_hBitmapMask, sizeof(BITMAP), &m_BitmapInfoMask);
	m_hMemDCMask = CreateCompatibleDC(m_hScreenDC);
	SelectObject(m_hMemDCMask, m_hBitmapMask); // m_hOldBitmap = (HBITMAP)... 이미 old 저장했으므로 생략...
	return true;
}

HBITMAP bgBitmap::GetRotationBitmap(HDC hdc, RECT& rect, int iWidth, int iHeight, float fAngle)
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
	float fSin = (float)sin(fRadian);
	float fCos = (float)cos(fRadian);
	XFORM xForm;
	xForm.eM11 = fCos;
	xForm.eM12 = -fSin;
	xForm.eM21 = fSin;
	xForm.eM22 = fCos;
	xForm.eDx = iWidth / 2.0f;
	xForm.eDy = iHeight / 2.0f;
	int iGraphicsModeOld = SetGraphicsMode(hScreenDC, GM_ADVANCED);
	SetWorldTransform(hScreenDC, &xForm);

	// 출력~!!!
	BitBlt(hScreenDC, -(rect.right / 2), -(rect.bottom / 2), rect.right, rect.bottom, hdc, rect.left, rect.top, SRCCOPY);

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

bool bgBitmap::Draw(HDC hdc, POINT pos, RECT rect, DWORD mode, bool bRotation, float fAngle)
{
	if (!bRotation)
	{
		if (m_bMask)
			BitBlt(hdc, pos.x, pos.y, rect.right, rect.bottom, m_hMemDCMask, rect.left, rect.top, mode);
		BitBlt(hdc, pos.x, pos.y, rect.right, rect.bottom, m_hMemDC, rect.left, rect.top, mode);
	}
	else
	{
		int iWidth, iHeight;
		if (rect.right > rect.bottom)
			iWidth = iHeight = rect.right;
		else
			iWidth = iHeight = rect.bottom;

		HBITMAP hBitmapMask = GetRotationBitmap(m_hMemDCMask, rect, iWidth, iHeight, fAngle);
		HBITMAP hBitmap = GetRotationBitmap(m_hMemDC, rect, iWidth, iHeight, fAngle);

		HDC hMemDCMask = CreateCompatibleDC(m_hScreenDC);
		HDC hMemDC = CreateCompatibleDC(m_hScreenDC);

		HBITMAP hOldMask = (HBITMAP)SelectObject(hMemDCMask, hBitmapMask);
		HBITMAP hOld = (HBITMAP)SelectObject(hMemDC, hBitmap);

		BitBlt(m_hScreenDC, pos.x, pos.y, iWidth, iHeight, hMemDCMask, 0, 0, SRCAND);
		BitBlt(m_hScreenDC, pos.x, pos.y, iWidth, iHeight, hMemDC, 0, 0, SRCINVERT);
		BitBlt(m_hScreenDC, pos.x, pos.y, iWidth, iHeight, hMemDCMask, 0, 0, SRCINVERT);

		SelectObject(hMemDCMask, hOldMask);
		SelectObject(hMemDC, hOld);
		DeleteDC(hMemDCMask);
		DeleteDC(hMemDC);
		DeleteObject(hBitmapMask);
		DeleteObject(hBitmap);
	}
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
	return true;
}

bool bgBitmap::Release()
{
	SelectObject(m_hMemDC, m_hOldBitmap);
	ReleaseDC(g_hWnd, m_hMemDC);

	SelectObject(m_hMemDCMask, m_hOldBitmap);
	ReleaseDC(g_hWnd, m_hMemDCMask);
	return true;
}

bgBitmap::bgBitmap()
{
	m_bMask = false;
}


bgBitmap::~bgBitmap()
{
}
