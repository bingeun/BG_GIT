#include "objBullet.h"
#include "GameMain.h"


bool objBullet::Init()
{
	//bgObject::Init();
	SetDC(g_hOffScreenDC);

	I_SpriteMgr.Add(L"../../data/bgPangPang/bullet.txt");
	SetBitmap(L"bullet.bmp");

	return true;
}

bool objBullet::Frame()
{
	//bgObject::Frame();
	
	switch (m_BulletType)
	{
	case BULLET_GUN:
	case BULLET_GUN_LEFT:
	case BULLET_GUN_RIGHT:
		m_fPosYHead -= g_fSPF * BULLET_SPEED * 2;
		break;
	default:
		m_fPosYHead -= g_fSPF * BULLET_SPEED;
		break;
	}

	if (m_fPosYHead < BOARD_Y)
	{
		m_fPosYHead = BOARD_Y;
	}
	return true;
}

bool objBullet::Render()
{
	//bgObject::Render();
	if (m_pSprite->m_iterFrame->pBitmap)
	{
		POINT posBullet;
		int y;
		switch (m_BulletType)
		{
		case BULLET_SINGLE:
			SetSprite(L"BulletSingleMid");
			for (y = (int)(m_fPosY + HERO_H - BLOCK_H); y > m_fPosYHead; y -= BLOCK_H)
			{
				posBullet.x = m_posObject.x;
				posBullet.y = y;
				m_pSprite->m_iterFrame->pBitmap->Draw(m_hOffScreenDC, posBullet, m_pSprite->m_iterFrame->rectSrc);
			}
			SetSprite(L"BulletSingle");
			posBullet.x = m_posObject.x;
			posBullet.y = (int)m_fPosYHead;
			m_pSprite->m_iterFrame->pBitmap->Draw(m_hOffScreenDC, posBullet, m_pSprite->m_iterFrame->rectSrc);
			break;

		case BULLET_DOUBLE:
			SetSprite(L"BulletDoubleMid");
			for (y = (int)(m_fPosY + HERO_H - BLOCK_H); y > m_fPosYHead; y -= BLOCK_H)
			{
				posBullet.x = m_posObject.x;
				posBullet.y = y;
				m_pSprite->m_iterFrame->pBitmap->Draw(m_hOffScreenDC, posBullet, m_pSprite->m_iterFrame->rectSrc);
			}
			SetSprite(L"BulletDouble");
			posBullet.x = m_posObject.x;
			posBullet.y = (int)m_fPosYHead;
			m_pSprite->m_iterFrame->pBitmap->Draw(m_hOffScreenDC, posBullet, m_pSprite->m_iterFrame->rectSrc);
			break;

		case BULLET_FIXED:
			SetSprite(L"BulletFixedMid");
			for (y = (int)(m_fPosY + HERO_H - BLOCK_H); y > m_fPosYHead; y -= BLOCK_H)
			{
				posBullet.x = m_posObject.x;
				posBullet.y = y;
				m_pSprite->m_iterFrame->pBitmap->Draw(m_hOffScreenDC, posBullet, m_pSprite->m_iterFrame->rectSrc);
			}
			SetSprite(L"BulletFixed");
			posBullet.x = m_posObject.x;
			posBullet.y = (int)m_fPosYHead;
			m_pSprite->m_iterFrame->pBitmap->Draw(m_hOffScreenDC, posBullet, m_pSprite->m_iterFrame->rectSrc);
			break;

		case BULLET_GUN:
			SetSprite(L"BulletGun");
			posBullet.x = m_posObject.x;
			posBullet.y = (int)m_fPosYHead;
			m_pSprite->m_iterFrame->pBitmap->Draw(m_hOffScreenDC, posBullet, m_pSprite->m_iterFrame->rectSrc);
			break;

		case BULLET_GUN_LEFT:
			SetSprite(L"BulletGunLeft");
			posBullet.x = m_posObject.x;
			posBullet.y = (int)m_fPosYHead;
			m_pSprite->m_iterFrame->pBitmap->Draw(m_hOffScreenDC, posBullet, m_pSprite->m_iterFrame->rectSrc);
			break;

		case BULLET_GUN_RIGHT:
			SetSprite(L"BulletGunRight");
			posBullet.x = m_posObject.x;
			posBullet.y = (int)m_fPosYHead;
			m_pSprite->m_iterFrame->pBitmap->Draw(m_hOffScreenDC, posBullet, m_pSprite->m_iterFrame->rectSrc);
			break;
		}
	}
	return true;
}

bool objBullet::Release()
{
	//bgObject::Release();
	return true;
}

objBullet::objBullet()
{
}


objBullet::~objBullet()
{
}
