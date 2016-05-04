#include "objHero.h"
#include "GameMain.h"


void objHero::Left()
{
	m_isLeft = true;
	m_fPosX -= g_fSPF * m_fSpeed;
	if ((int)m_fPosX < BOARD_X - (HERO_W / 5))
		m_fPosX = (float)(BOARD_X - (HERO_W / 5));
	m_posObject.x = (int)m_fPosX;
}

void objHero::Right()
{
	m_isLeft = false;
	m_fPosX += g_fSPF * m_fSpeed;
	if ((int)m_fPosX > CLIENT_W - BOARD_X - HERO_W + (HERO_W / 5))
		m_fPosX = (float)(CLIENT_W - BOARD_X - HERO_W + (HERO_W / 5));
	m_posObject.x = (int)m_fPosX;
}

void objHero::Up()
{
	m_posObject.y -= (int)(g_fSPF * m_fSpeed);
	m_fPosY = (float)(m_posObject.y);
}

void objHero::Down()
{
	m_posObject.y += (int)(g_fSPF * m_fSpeed);
	m_fPosY = (float)(m_posObject.y);
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

	I_FrameMgr.Add(L"../../data/bgPangPang/hero.txt");
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
	if (m_Sprite.m_iterFrame->pBitmap)
	{
		// ★★★★★★★★★★★★★★★★ 회전, 반전 출력 디버깅 필요 ★★★★★★★★★★★★★★★★
		//m_Sprite.m_iterFrame->pBitmap->Draw(m_hOffScreenDC, m_posObject, m_Sprite.m_iterFrame->rectSrc, true, false);
		//m_Sprite.m_iterFrame->pBitmap->Draw(m_hOffScreenDC, m_posObject, m_Sprite.m_iterFrame->rectSrc, false, false, 90.0f, SRCCOPY);
		m_Sprite.m_iterFrame->pBitmap->Draw(m_hOffScreenDC, m_posObject, m_Sprite.m_iterFrame->rectSrc);
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
