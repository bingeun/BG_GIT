#include "objItem.h"
#include "GameMain.h"


bool objItem::Init()
{
	//bgObject::Init();
	SetDC(g_hOffScreenDC);

	// ������� �ε��ϴ� ������ ���ؼ� ���ο��� �ε�...
	// I_FrameMgr.Add(L"../../data/bgPangPang/item.txt");
	SetBitmap(L"item.bmp");
	m_bLife = false;

	return true;
}

bool objItem::Frame()
{
	//bgObject::Frame();
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
