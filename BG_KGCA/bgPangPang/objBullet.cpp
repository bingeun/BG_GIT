#include "objBullet.h"
#include "GameMain.h"


bool objBullet::Init()
{
	//bgObject::Init();
	SetDC(g_hOffScreenDC);

	// ������� �ε��ϴ� ������ ���ؼ� ���ο��� �ε�...
	// I_FrameMgr.Add(L"../../data/bgPangPang/bullet.txt");
	SetBitmap(L"bullet.bmp");
	m_bLife = false;

	return true;
}

bool objBullet::Frame()
{
	//bgObject::Frame();
	
	switch (m_BulletType)
	{
	case BULLET_GUN:
		m_fPosYHead -= g_fSPF * BULLET_SPEED * 1.8f;
		break;
	case BULLET_GUN_LEFT:
		m_fPosYHead -= g_fSPF * BULLET_SPEED * 1.8f;
		m_fPosX -= g_fSPF * 70.0f;
		m_posObject.x = (int)m_fPosX;
		break;
	case BULLET_GUN_RIGHT:
		m_fPosYHead -= g_fSPF * BULLET_SPEED * 1.8f;
		m_fPosX += g_fSPF * 70.0f;
		m_posObject.x = (int)m_fPosX;
		break;
	default:
		m_fPosYHead -= g_fSPF * BULLET_SPEED;
		break;
	}

	// ���� ������ �����...
	if (m_fPosYHead < BOARD_Y)
	{
		// ������ �ۻ��� �����Ǵ� �ð� ó��...
		if (m_BulletType == BULLET_FIXED)
		{
			if (g_fAccumulation - m_fShotTime < 3.0f)
			{
				m_fPosYHead = BOARD_Y;
			}
			else
			{
				m_bLife = false;
			}
		}
		else
		{
			m_bLife = false;
		}
	}
	return true;
}

bool objBullet::Render()
{
	//bgObject::Render();
	if (m_Sprite.m_iterFrame->pBitmap)
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
				m_Sprite.m_iterFrame->pBitmap->Draw(m_hOffScreenDC, posBullet, m_Sprite.m_iterFrame->rectSrc);
			}
			SetSprite(L"BulletSingle");
			posBullet.x = m_posObject.x;
			posBullet.y = (int)m_fPosYHead;
			m_Sprite.m_iterFrame->pBitmap->Draw(m_hOffScreenDC, posBullet, m_Sprite.m_iterFrame->rectSrc);
			break;

		case BULLET_DOUBLE:
			SetSprite(L"BulletDoubleMid");
			for (y = (int)(m_fPosY + HERO_H - BLOCK_H); y > m_fPosYHead; y -= BLOCK_H)
			{
				posBullet.x = m_posObject.x;
				posBullet.y = y;
				m_Sprite.m_iterFrame->pBitmap->Draw(m_hOffScreenDC, posBullet, m_Sprite.m_iterFrame->rectSrc);
			}
			SetSprite(L"BulletDouble");
			posBullet.x = m_posObject.x;
			posBullet.y = (int)m_fPosYHead;
			m_Sprite.m_iterFrame->pBitmap->Draw(m_hOffScreenDC, posBullet, m_Sprite.m_iterFrame->rectSrc);
			break;

		case BULLET_FIXED:
			SetSprite(L"BulletFixedMid");
			for (y = (int)(m_fPosY + HERO_H - BLOCK_H); y > m_fPosYHead; y -= BLOCK_H)
			{
				posBullet.x = m_posObject.x;
				posBullet.y = y;
				m_Sprite.m_iterFrame->pBitmap->Draw(m_hOffScreenDC, posBullet, m_Sprite.m_iterFrame->rectSrc);
			}
			SetSprite(L"BulletFixed");
			posBullet.x = m_posObject.x;
			posBullet.y = (int)m_fPosYHead;
			m_Sprite.m_iterFrame->pBitmap->Draw(m_hOffScreenDC, posBullet, m_Sprite.m_iterFrame->rectSrc);
			break;

		case BULLET_GUN:
			SetSprite(L"BulletGun");
			posBullet.x = m_posObject.x;
			posBullet.y = (int)m_fPosYHead;
			m_Sprite.m_iterFrame->pBitmap->Draw(m_hOffScreenDC, posBullet, m_Sprite.m_iterFrame->rectSrc);
			break;

		case BULLET_GUN_LEFT:
			SetSprite(L"BulletGunLeft");
			posBullet.x = m_posObject.x;
			posBullet.y = (int)m_fPosYHead;
			m_Sprite.m_iterFrame->pBitmap->Draw(m_hOffScreenDC, posBullet, m_Sprite.m_iterFrame->rectSrc);
			break;

		case BULLET_GUN_RIGHT:
			SetSprite(L"BulletGunRight");
			posBullet.x = m_posObject.x;
			posBullet.y = (int)m_fPosYHead;
			m_Sprite.m_iterFrame->pBitmap->Draw(m_hOffScreenDC, posBullet, m_Sprite.m_iterFrame->rectSrc);
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
