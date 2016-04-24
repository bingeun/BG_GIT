#include "bgHero.h"


bool bgHero::Init()
{
	bgObject::Init();
	SetDC(g_hOffScreenDC);

	// 비트맵 추가 및 초기화
	I_SpriteMgr.Add(L"../../data/airplane.txt");
	m_iBitmap = I_BitmapMgr.GetKey(L"airplane.bmp");
	m_pBitmap = I_BitmapMgr.GetPtr(m_iBitmap);
	m_pBitmap->SetDC(g_hOffScreenDC);

	m_iSprite = I_SpriteMgr.GetKey(L"rectHero");
	m_pSprite = I_SpriteMgr.GetPtr(m_iSprite);
	m_pSprite->Init();

	// 주인공 초기화
	m_posObject.x = 800 / 2;
	m_posObject.y = 600 / 2;
	m_fSpeed = 1000.0f;

	return true;
}

bool bgHero::Frame()
{
	bgObject::Frame();
	return true;
}

bool bgHero::Render()
{
	//bgObject::Render();
	if (m_pSprite->m_iterFrame->pBitmap)
		m_pSprite->m_iterFrame->pBitmap->Draw(m_hOffScreenDC, m_posObject, m_pSprite->m_iterFrame->rectSrc, m_fDirection, SRCCOPY);
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
