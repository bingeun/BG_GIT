#include "objHero.h"


void objHero::Left()
{
	m_posObject.x -= (int)(g_fSPF * m_fSpeed);
	m_isLeft = true;
}

void objHero::Right()
{
	m_posObject.x += (int)(g_fSPF * m_fSpeed);
	m_isLeft = false;
}

void objHero::Up()
{
	m_posObject.y -= (int)(g_fSPF * m_fSpeed);
}

void objHero::Down()
{
	m_posObject.y += (int)(g_fSPF * m_fSpeed);
}

void objHero::SpeedUp(float fSpeedUp)
{
	m_fSpeed += fSpeedUp;
}

void objHero::SpeedDown(float fSpeedDown)
{
	m_fSpeed -= fSpeedDown;
}

void objHero::DirectionLeft(float fDirection)
{
	m_fDirection += fDirection;
	m_fDirection = (m_fDirection >= 360.0f) ? 0.0f : m_fDirection;
}

void objHero::DirectionRight(float fDirection)
{
	m_fDirection += fDirection;
	m_fDirection = (m_fDirection >= 360.0f) ? 0.0f : m_fDirection;
}

bool objHero::Init()
{
	//bgObject::Init();
	SetDC(g_hOffScreenDC);

	I_SpriteMgr.Add(L"../../data/bgPangPang/hero.txt");
	SetBitmap(L"hero.bmp");
	SetSprite(L"HeroIdle");

	m_isLeft = true;
	
	return true;
}

bool objHero::Frame()
{
	bgObject::Frame();
	return true;
}

bool objHero::Render()
{
	//bgObject::Render();
	if (m_pSprite->m_iterFrame->pBitmap)
	{
		// ★★★★★★★★★★★★★★★★ 회전, 반전 출력 디버깅 필요 ★★★★★★★★★★★★★★★★
		//m_pSprite->m_iterFrame->pBitmap->Draw(m_hOffScreenDC, m_posObject, m_pSprite->m_iterFrame->rectSrc, true, false);
		//m_pSprite->m_iterFrame->pBitmap->Draw(m_hOffScreenDC, m_posObject, m_pSprite->m_iterFrame->rectSrc, false, false, 90.0f, SRCCOPY);
		m_pSprite->m_iterFrame->pBitmap->Draw(m_hOffScreenDC, m_posObject, m_pSprite->m_iterFrame->rectSrc);
	}
	return true;
}

bool objHero::Release()
{
	//bgObject::Release();
	return true;
}

objHero::objHero()
{
}


objHero::~objHero()
{
}
