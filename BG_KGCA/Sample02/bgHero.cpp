#include "bgHero.h"


bool bgHero::Init()
{
	bgObject::Init();
	m_iBitmap = I_BitmapMgr.GetKey(L"airplane.bmp");
	m_pBitmap = I_BitmapMgr.GetPtr(m_iBitmap);
	m_iSprite = I_SpriteMgr.GetKey(L"rectHero");
	m_pSprite = I_SpriteMgr.GetPtr(m_iSprite);

	m_fSpeed = 30.0f;
	m_posObject = { 800 / 2, 600 / 2 };
	m_rectObject = m_pSprite->m_Frame[0].rectSrc;
	return true;
}

bool bgHero::Frame()
{
	bgObject::Frame();
	return true;
}

bool bgHero::Render()
{
	bgObject::Render();
	m_pBitmap->Draw(g_hOffScreenDC, m_posObject, m_rectObject);
	return true;
}

bool bgHero::Release()
{
	bgObject::Release();
	return true;
}

bgHero::bgHero()
{
}


bgHero::~bgHero()
{
}
