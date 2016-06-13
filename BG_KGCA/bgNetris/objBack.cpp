#include "objBack.h"


bool objBack::Init()
{
	//bgObject::Init();
	SetDC(g_hOffScreenDC);

	I_FrameMgr.Add(L"../../data/bgNetris/main.txt");
	I_FrameMgr.Add(L"../../data/bgNetris/net_back.txt");
	SetBitmap(L"main.bmp");
	SetSprite(L"Main");

	m_posObject.x = 0;
	m_posObject.y = 0;
	m_fSpeed = 1000.0f;

	return true;
}

bool objBack::Frame()
{
	//bgObject::Frame();
	return true;
}

bool objBack::Render()
{
	//bgObject::Render();

	if (m_Sprite.m_iterFrame->pBitmap)
		m_Sprite.m_iterFrame->pBitmap->Draw(m_hOffScreenDC, m_posObject, m_Sprite.m_iterFrame->rectSrc);
	return true;
}

bool objBack::Release()
{
	//bgObject::Release();
	return true;
}

objBack::objBack()
{
}


objBack::~objBack()
{
}
