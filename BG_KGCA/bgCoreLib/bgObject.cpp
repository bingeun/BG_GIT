#include "bgObject.h"


bool bgObject::Load(HDC hScreenDC, HDC hOffScreenDC, TCHAR* pszName, TCHAR* pszNameMask)
{
	m_hScreenDC = hScreenDC;
	m_hOffScreenDC = hOffScreenDC;

	return false;
}

void bgObject::SetObject(RECT rect, POINT pos, float fSpeed)
{
	m_rectObject = rect;
	m_posObject = pos;
	m_fSpeed = fSpeed;
}

void bgObject::Left()
{
	m_posObject.x -= (int)(g_fSPF * m_fSpeed);
}

void bgObject::Right()
{
	m_posObject.x += (int)(g_fSPF * m_fSpeed);
}

void bgObject::Up()
{
	m_posObject.y -= (int)(g_fSPF * m_fSpeed);
}

void bgObject::Down()
{
	m_posObject.y += (int)(g_fSPF * m_fSpeed);
}

bool bgObject::Init()
{
	m_fSpeed = 30.0f;
	m_posObject.x = 800 / 2;
	m_posObject.y = 600 / 2;
	return true;
}

bool bgObject::Frame()
{
	return true;
}

bool bgObject::Render()
{
	if(m_pBitmap)
		m_pBitmap->Draw(m_hScreenDC, m_posObject, m_rectObject);
	return true;
}

bool bgObject::Release()
{
	return true;
}

bgObject::bgObject()
{
}


bgObject::~bgObject()
{
}
