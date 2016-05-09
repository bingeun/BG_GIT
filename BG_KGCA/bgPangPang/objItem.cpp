#include "objItem.h"
#include "GameMain.h"


bool objItem::Init()
{
	//bgObject::Init();
	SetDC(g_hOffScreenDC);

	// 개수대로 로드하는 문제로 인해서 메인에서 로드...
	// I_FrameMgr.Add(L"../../data/bgPangPang/item.txt");
	SetBitmap(L"item.bmp");
	m_bLife = false;
	m_fLifeTime = 0.0f;
	m_fPosA = 0.0f;
	m_fPosB = ITEM_DROP_SPEED;

	return true;
}

bool objItem::Frame()
{
//	bgObject::Frame();
	m_fPosX += g_fSPF * m_fPosA;
	m_fPosY += g_fSPF * m_fPosB;
	if ((int)m_fPosY > BOARD_Y + BOARD_H*BLOCK_H - ITEM_H)
		m_fPosY = BOARD_Y + BOARD_H*BLOCK_H - ITEM_H;
	m_posObject.x = (int)m_fPosX;
	m_posObject.y = (int)m_fPosY;

	if (g_fAccumulation - m_fLifeTime > LIFETIME_ITEM)
		m_bLife = false;
	return true;
}

bool objItem::Render()
{
	//bgObject::Render();
	if (m_Sprite.m_iterFrame->pBitmap)
		m_Sprite.m_iterFrame->pBitmap->Draw(m_hOffScreenDC, m_posObject, m_Sprite.m_iterFrame->rectSrc);
	return true;
}

bool objItem::Release()
{
	//bgObject::Release();
	return true;
}

objItem::objItem()
{
}


objItem::~objItem()
{
}
