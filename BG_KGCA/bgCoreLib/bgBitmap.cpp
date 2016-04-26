#include "bgBitmap.h"


bool bgBitmap::Load(TCHAR* pszName, TCHAR* pszNameMask)
{
	// ���ϰ�θ� �и��� ��ҵ��� ������ ���� ����
	TCHAR Drive[MAX_PATH] = { 0, };
	TCHAR Dir[MAX_PATH] = { 0, };
	TCHAR Name[MAX_PATH] = { 0, };
	TCHAR Ext[MAX_PATH] = { 0, };
	TCHAR NameExt[MAX_PATH] = { 0, };

	// �̹��� �ҷ�����...
	m_hBitmap = (HBITMAP)LoadImage(g_hInstance, pszName, IMAGE_BITMAP, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE);
	if (m_hBitmap == NULL)
	{
		m_bMask = false;
		return false;
	}

	GetObject(m_hBitmap, sizeof(BITMAP), &m_BitmapInfo);
	m_hMemDC = CreateCompatibleDC(m_hOffScreenDC);
	m_hOldBitmap = (HBITMAP)SelectObject(m_hMemDC, m_hBitmap);

	// ���ϰ�θ� ��Һ��� �и� ��, [���ϸ�.Ȯ����] ���·� ��������� ����
	_tsplitpath_s(pszName, Drive, Dir, Name, Ext);
	Ext[4] = 0;
	memset(NameExt, 0, sizeof(TCHAR) * MAX_PATH);
	_stprintf_s(NameExt, _T("%s%s"), Name, Ext);
	m_szName = NameExt;

	// ====================== ����ũ ������ �����ߴٸ�... ========================
	if (pszNameMask)
	{
		// �̹��� �ҷ�����
		m_hBitmapMask = (HBITMAP)LoadImage(g_hInstance, pszNameMask, IMAGE_BITMAP, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE);
		if (m_hBitmapMask == NULL)
		{
			m_bMask = false;
			return true;
		}
		m_bMask = true;

		GetObject(m_hBitmapMask, sizeof(BITMAP), &m_BitmapInfoMask);
		m_hMemDCMask = CreateCompatibleDC(m_hOffScreenDC);
		SelectObject(m_hMemDCMask, m_hBitmapMask); // m_hOldBitmap = (HBITMAP)... �̹� old ���������Ƿ� ����...

		// ���ϰ�θ� ��Һ��� �и� ��, [���ϸ�.Ȯ����] ���·� ��������� ����
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
	m_hMemDC = CreateCompatibleDC(m_hOffScreenDC);
	m_hOldBitmap = (HBITMAP)SelectObject(m_hMemDC, m_hBitmap);

	m_hBitmapMask = LoadBitmap(g_hInstance, MAKEINTRESOURCE(dwBitmap));
	GetObject(m_hBitmapMask, sizeof(BITMAP), &m_BitmapInfoMask);
	m_hMemDCMask = CreateCompatibleDC(m_hOffScreenDC);
	SelectObject(m_hMemDCMask, m_hBitmapMask); // m_hOldBitmap = (HBITMAP)... �̹� old ���������Ƿ� ����...
	return true;
}

HBITMAP bgBitmap::GetRotationBitmap(HDC hdc, RECT& rect, int iWidth, int iHeight, float fAngle)
{
	// ���ο� ��Ʈ�� ���� �� �ʱ�ȭ
	HDC		hScreenDC = CreateCompatibleDC(m_hOffScreenDC);
	HBITMAP	hBitmapResult = CreateCompatibleBitmap(m_hOffScreenDC, iWidth, iHeight);
	HBITMAP hBitmapOld = (HBITMAP)SelectObject(hScreenDC, hBitmapResult);

	COLORREF rgbBack = RGB(0xFF, 0xFF, 0xFF);
	HBRUSH   hBrushBack = CreateSolidBrush(rgbBack);
	HBRUSH   hBrushOld = (HBRUSH)SelectObject(hScreenDC, hBrushBack);
	PatBlt(hScreenDC, 0, 0, iWidth, iHeight, PATCOPY);
	DeleteObject(SelectObject(hScreenDC, hBrushOld));

	// ȸ��
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

	// ���~!!!
	BitBlt(hScreenDC, -(rect.right / 2), -(rect.bottom / 2), rect.right, rect.bottom, hdc, rect.left, rect.top, SRCCOPY);

	// ���󺹱�
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

HBITMAP bgBitmap::GetInvertBitmap(HDC hdc, RECT& rect, int iWidth, int iHeight, bool bInvertH, bool bInvertV)
{
	// ���ο� ��Ʈ�� ���� �� �ʱ�ȭ
	HDC		hScreenDC = CreateCompatibleDC(m_hOffScreenDC);
	HBITMAP	hBitmapResult = CreateCompatibleBitmap(m_hOffScreenDC, iWidth, iHeight);
	HBITMAP hBitmapOld = (HBITMAP)SelectObject(hScreenDC, hBitmapResult);

	COLORREF rgbBack = RGB(0xFF, 0xFF, 0xFF);
	HBRUSH   hBrushBack = CreateSolidBrush(rgbBack);
	HBRUSH   hBrushOld = (HBRUSH)SelectObject(hScreenDC, hBrushBack);
	PatBlt(hScreenDC, 0, 0, iWidth, iHeight, PATCOPY);
	DeleteObject(SelectObject(hScreenDC, hBrushOld));

	// ȸ��
	XFORM xForm;
	xForm.eM11 = (bInvertH) ? 1.0f : 1.0f;
	xForm.eM12 = 0;
	xForm.eM21 = 0;
	xForm.eM22 = (bInvertV) ? 1.0f : 1.0f;
	xForm.eDx = iWidth / 2.0f;
	xForm.eDy = iHeight / 2.0f;
	int iGraphicsModeOld = SetGraphicsMode(hScreenDC, GM_ADVANCED);
	SetWorldTransform(hScreenDC, &xForm);

	// ���~!!!
	BitBlt(hScreenDC, -(rect.right / 2), -(rect.bottom / 2), rect.right, rect.bottom, hdc, rect.left, rect.top, SRCCOPY);

	// ���󺹱�
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

bool bgBitmap::Draw(HDC hdc, POINT pos, RECT rect, bool bInvertH, bool bInvertV, float fAngle, DWORD dwMode)
{
	bool bRotation = (fAngle) ? true : false;

	// ����, �¿���� ����̸�...
	if (bInvertH || bInvertV)
	{
		int iWidth, iHeight;
		if (rect.right > rect.bottom)
			iWidth = iHeight = rect.right;
		else
			iWidth = iHeight = rect.bottom;

		HBITMAP hBitmapMask = NULL;
		HDC hMemDCMask = NULL;
		HBITMAP hOldMask = NULL;

		HBITMAP hBitmap = GetInvertBitmap(m_hMemDC, rect, iWidth, iHeight, bInvertH, bInvertV);
		HDC hMemDC = CreateCompatibleDC(hdc);
		HBITMAP hOld = (HBITMAP)SelectObject(hMemDC, hBitmap);

		if (m_bMask)
		{
			hBitmapMask = GetInvertBitmap(m_hMemDCMask, rect, iWidth, iHeight, bInvertH, bInvertV);
			hMemDCMask = CreateCompatibleDC(hdc);
			hOldMask = (HBITMAP)SelectObject(hMemDCMask, hBitmapMask);
			BitBlt(hdc, pos.x, pos.y, iWidth, iHeight, hMemDCMask, 0, 0, SRCAND);
		}
		BitBlt(hdc, pos.x, pos.y, iWidth, iHeight, hMemDC, 0, 0, SRCINVERT);
		if (m_bMask)
		{
			BitBlt(hdc, pos.x, pos.y, iWidth, iHeight, hMemDCMask, 0, 0, SRCINVERT);
			SelectObject(hMemDCMask, hOldMask);
			DeleteDC(hMemDCMask);
			DeleteObject(hBitmapMask);
		}

		SelectObject(hMemDC, hOld);
		DeleteDC(hMemDC);
		DeleteObject(hBitmap);
	}
	// ȸ�� ����̸�...
	else if (bRotation)
	{
		int iWidth, iHeight;
		if (rect.right > rect.bottom)
			iWidth = iHeight = rect.right;
		else
			iWidth = iHeight = rect.bottom;

		HBITMAP hBitmapMask = NULL;
		HDC hMemDCMask = NULL;
		HBITMAP hOldMask = NULL;

		HBITMAP hBitmap = GetRotationBitmap(m_hMemDC, rect, iWidth, iHeight, fAngle);
		HDC hMemDC = CreateCompatibleDC(hdc);
		HBITMAP hOld = (HBITMAP)SelectObject(hMemDC, hBitmap);

		if (m_bMask)
		{
			hBitmapMask = GetRotationBitmap(m_hMemDCMask, rect, iWidth, iHeight, fAngle);
			hMemDCMask = CreateCompatibleDC(hdc);
			hOldMask = (HBITMAP)SelectObject(hMemDCMask, hBitmapMask);
			BitBlt(hdc, pos.x, pos.y, iWidth, iHeight, hMemDCMask, 0, 0, SRCAND);
		}
		BitBlt(hdc, pos.x, pos.y, iWidth, iHeight, hMemDC, 0, 0, SRCINVERT);
		if (m_bMask)
		{
			BitBlt(hdc, pos.x, pos.y, iWidth, iHeight, hMemDCMask, 0, 0, SRCINVERT);
			SelectObject(hMemDCMask, hOldMask);
			DeleteDC(hMemDCMask);
			DeleteObject(hBitmapMask);
		}

		SelectObject(hMemDC, hOld);
		DeleteDC(hMemDC);
		DeleteObject(hBitmap);
	}
	// ȸ��or���� ����� �ƴϸ�...
	else
	{
		if (m_bMask)
		{
			BitBlt(hdc, pos.x, pos.y, rect.right, rect.bottom, m_hMemDCMask, rect.left, rect.top, SRCAND);
			BitBlt(hdc, pos.x, pos.y, rect.right, rect.bottom, m_hMemDC, rect.left, rect.top, SRCINVERT);
			BitBlt(hdc, pos.x, pos.y, rect.right, rect.bottom, m_hMemDCMask, rect.left, rect.top, SRCINVERT);
		}
		else
		{
			BitBlt(hdc, pos.x, pos.y, rect.right, rect.bottom, m_hMemDC, rect.left, rect.top, dwMode);
		}
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
