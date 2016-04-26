#include "bgGround.h"


bool bgGround::Init()
{
	bgObject::Init();
	SetDC(g_hOffScreenDC);

	// 비트맵 추가 및 초기화
	I_SpriteMgr.Add(L"../../data/airplane.txt");
	m_iBitmap = I_BitmapMgr.GetKey(L"background.bmp");
	m_pBitmap = I_BitmapMgr.GetPtr(m_iBitmap);
	m_pBitmap->SetDC(g_hOffScreenDC);

	m_iSprite = I_SpriteMgr.GetKey(L"rectGround");
	m_pSprite = I_SpriteMgr.GetPtr(m_iSprite);
	m_pSprite->Init();

	// 초기화
	m_posObject.x = 0;
	m_posObject.y = 0;
	m_fSpeed = 1000.0f;

	return true;
}

bool bgGround::Frame()
{
	bgObject::Frame();
	return true;
}

bool bgGround::Render()
{
	//bgObject::Render();
	if (m_pSprite->m_iterFrame->pBitmap)
		m_pSprite->m_iterFrame->pBitmap->Draw(m_hOffScreenDC, m_posObject, m_pSprite->m_iterFrame->rectSrc);
	return true;
}

bool bgGround::Release()
{
	bgObject::Release();
	return true;
}

bgGround::bgGround()
{
}


bgGround::~bgGround()
{
}
