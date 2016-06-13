#include "objUI.h"


bool objUI::Init()
{
	//bgObject::Init();
	SetDC(g_hOffScreenDC);

	I_FrameMgr.Add(L"../../data/bgNetris/ui.txt");
	SetBitmap(L"ui.bmp");

	m_posObject.x = 689;
	m_posObject.y = 15;
	m_fSpeed = 1000.0f;

	return true;
}

bool objUI::Frame()
{
	//bgObject::Frame();
	return true;
}

bool objUI::Render()
{
	//bgObject::Render();

	if (m_Sprite.m_iterFrame->pBitmap)
		m_Sprite.m_iterFrame->pBitmap->Draw(m_hOffScreenDC, m_posObject, m_Sprite.m_iterFrame->rectSrc);
	return true;
}

bool objUI::Release()
{
	//bgObject::Release();
	return true;
}

objUI::objUI()
{
}


objUI::~objUI()
{
}
