#include "objFont.h"
#include "GameMain.h"


void objFont::PrintNumber(int iNumber, int pX, int pY)
{
	int iMod, iFontWidth;

	SetSprite(L"FontNumberBig");
	iFontWidth = m_Sprite.m_iterFrame->rectSrc.right;
	m_posObject.y = pY;
	do
	{
		iMod = iNumber % 10;
		iNumber /= 10;
		pX -= iFontWidth;

		SetSprite(L"FontNumberBig");
		m_Sprite.m_iterFrame += iMod;

		m_posObject.x = pX;
		if (m_Sprite.m_iterFrame->pBitmap)
			m_Sprite.m_iterFrame->pBitmap->Draw(m_hOffScreenDC, m_posObject, m_Sprite.m_iterFrame->rectSrc);
	} while (iNumber);
}

bool objFont::Init()
{
	//bgObject::Init();
	SetDC(g_hOffScreenDC);

	I_FrameMgr.Add(L"../../data/bgPangPang/font.txt");
	SetBitmap(L"font.bmp");

	return true;
}

bool objFont::Frame()
{
	//bgObject::Frame();
	return true;
}

bool objFont::Render()
{
	//bgObject::Render();
	if (m_Sprite.m_iterFrame->pBitmap)
		m_Sprite.m_iterFrame->pBitmap->Draw(m_hOffScreenDC, m_posObject, m_Sprite.m_iterFrame->rectSrc);
	return true;
}

bool objFont::Release()
{
	//bgObject::Release();
	return true;
}

objFont::objFont()
{
}


objFont::~objFont()
{
}
