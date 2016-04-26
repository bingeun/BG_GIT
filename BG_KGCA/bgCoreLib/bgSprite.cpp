#include "bgSprite.h"



bool bgSprite::Init()
{
	m_iterFrame = m_Frame.begin();
	m_fTimer = g_fAccumulation;
	return true;
}

bool bgSprite::Frame()
{
	if (g_fAccumulation - m_fTimer >= m_iterFrame->fLifeTime)
	{
		// 다음 프레임
		m_iterFrame++;
		if (m_iterFrame == m_Frame.end())
		{
			m_iterFrame = m_Frame.begin();
		}
		m_fTimer = g_fAccumulation;
	}
	return true;
}

bool bgSprite::Render()
{
	return true;
}

bool bgSprite::Release()
{
	return true;
}

bgSprite::bgSprite()
{
}


bgSprite::~bgSprite()
{
}
