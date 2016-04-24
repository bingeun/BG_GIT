#include "bgObject.h"


void bgObject::SetObject(float fPosX, float fPosY, float fSpeed)
{
	m_fPosX = fPosX;
	m_fPosY = fPosY;
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

void bgObject::SpeedUp(float fSpeedUp)
{
	m_fSpeed += fSpeedUp;
}

void bgObject::SpeedDown(float fSpeedDown)
{
	m_fSpeed -= fSpeedDown;
}

bool bgObject::Init()
{
	SetObject(800 / 2, 600 / 2, DEFAULT_SPEED);
	return true;
}

bool bgObject::Frame()
{
	m_posObject.x;
	m_posObject.y;

	return true;
}

bool bgObject::Render()
{
	if (m_pSprite->m_iterFrame->pBitmap)
		m_pSprite->m_iterFrame->pBitmap->Draw(m_hOffScreenDC, m_posObject, m_pSprite->m_iterFrame->rectSrc);

	m_pSprite->m_iterFrame++;
	if (m_pSprite->m_iterFrame == m_pSprite->m_Frame.end())
		m_pSprite->m_iterFrame = m_pSprite->m_Frame.begin();
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
