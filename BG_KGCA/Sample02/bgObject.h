#pragma once

struct bgRect
{
	int x, y;
	int w, h;
};

class bgObject
{
public:
	bgBitmap	m_Bitmap;
	bgRect	m_rt;
	bgRect	m_rtCollide;
	float	m_fPosX;
	float	m_fPosY;
	float	m_fSpeed;
	float	m_fDirection;

public:
	bool	Load(HDC hScreenDC, HDC hOffScreenDC, TCHAR* pFileName);
	void	SetPos(int iX, int iY);
	void	SetSpeed(float fSpeed = 1.0f);
	void	SetRect(int x, int y, int w, int h);

	void	Left();
	void	Right();
	void	Up();
	void	Down();

	bool	Draw();

public:
	bool	Init();
	bool	Frame();
	bool	Render();
	bool	Release();

public:
	bgObject();
	virtual ~bgObject();
};

