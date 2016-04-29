#include "objEffect.h"
#include "GameMain.h"


bool objEffect::Init()
{
	//bgObject::Init();
	SetDC(g_hOffScreenDC);

	// 개수대로 로드하는 문제로 인해서 메인에서 로드...
	// I_SpriteMgr.Add(L"../../data/bgPangPang/effect.txt");
	SetBitmap(L"effect.bmp");
	m_bLife = false;

	return true;
}

bool objEffect::Frame()
{
	//bgObject::Frame();
	if (!m_pSprite->Frame())
		m_bLife = false;

	switch (m_EffectType)
	{
	case EFFECT_NUCLEAR:
	{
	}
	break;

	case EFFECT_FLOWER:
	{
	}
	break;
	}
	return true;
}

bool objEffect::Render()
{
	//bgObject::Render();

	if (m_pSprite->m_iterFrame->pBitmap)
	{
		m_pSprite->m_iterFrame->pBitmap->Draw(m_hOffScreenDC, m_posObject, m_pSprite->m_iterFrame->rectSrc);
	}

	switch (m_EffectType)
	{
	case EFFECT_NUCLEAR:
	{
	}
	break;

	case EFFECT_FLOWER:
	{
	}
	break;
	}
	return true;
}

bool objEffect::Release()
{
	//bgObject::Release();
	return true;
}

objEffect::objEffect()
{
}


objEffect::~objEffect()
{
}
