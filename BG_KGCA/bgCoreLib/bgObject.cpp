#include "bgObject.h"


void bgObject::SetBitmap(TCHAR* pszBitmap)
{
	m_iBitmap = I_BitmapMgr.GetKey(pszBitmap);
	m_pBitmap = I_BitmapMgr.GetPtr(m_iBitmap);
	m_pBitmap->SetDC(m_hOffScreenDC);
}

void bgObject::SetSprite(TCHAR* pszSprite)
{
	m_Sprite.Init();
	m_iFrame = I_FrameMgr.GetKey(pszSprite);
	m_pFrame = I_FrameMgr.GetPtr(m_iFrame);
	m_Sprite.m_pFrame = m_pFrame;
	m_Sprite.m_iterFrame = m_Sprite.m_pFrame->m_vecFrame.begin();
}

void bgObject::SetObject(float fPosX, float fPosY, float fSpeed)
{
	m_posObject.x = (int)(fPosX);
	m_posObject.y = (int)(fPosY);
	m_fPosX = fPosX;
	m_fPosY = fPosY;
	m_fSpeed = fSpeed;
}

bool bgObject::Init()
{
	SetObject(0, 0, 30.0f);
	return true;
}

bool bgObject::Frame()
{
	m_Sprite.Frame();
	return true;
}

bool bgObject::Render()
{
	if (m_Sprite.m_iterFrame->pBitmap)
		m_Sprite.m_iterFrame->pBitmap->Draw(m_hOffScreenDC, m_posObject, m_Sprite.m_iterFrame->rectSrc);
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
