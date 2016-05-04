#include "objGround.h"


bool objGround::Init()
{
	//bgObject::Init();
	SetDC(g_hOffScreenDC);

	I_FrameMgr.Add(L"../../data/bgPangPang/main.txt");
	I_FrameMgr.Add(L"../../data/bgPangPang/back1.txt");
	I_FrameMgr.Add(L"../../data/bgPangPang/back2.txt");
	I_FrameMgr.Add(L"../../data/bgPangPang/back3.txt");
	I_FrameMgr.Add(L"../../data/bgPangPang/back4.txt");
	I_FrameMgr.Add(L"../../data/bgPangPang/gameover.txt");
	SetBitmap(L"main.bmp");
	SetSprite(L"Main");

	m_posObject.x = 0;
	m_posObject.y = 0;
	m_fSpeed = 1000.0f;

	return true;
}

bool objGround::Frame()
{
	//bgObject::Frame();
	return true;
}

bool objGround::Render()
{
	//bgObject::Render();

	if (m_Sprite.m_iterFrame->pBitmap)
		m_Sprite.m_iterFrame->pBitmap->Draw(m_hOffScreenDC, m_posObject, m_Sprite.m_iterFrame->rectSrc);
	return true;
}

bool objGround::Release()
{
	//bgObject::Release();
	return true;
}

objGround::objGround()
{
}


objGround::~objGround()
{
}
