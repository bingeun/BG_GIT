#include "bgSprite.h"



bool bgSprite::Init()
{
	m_iterFrame = m_Frame.begin();
	m_fTimer = g_fAccumulation;
	m_iCountLoop = 0;
	return true;
}

bool bgSprite::Frame()
{
	if (m_iNumLoop < 0)
	{
		if (g_fAccumulation - m_fTimer >= m_iterFrame->fLifeTime)
		{
			m_fTimer = g_fAccumulation;
			m_iterFrame++;
			if (m_iterFrame == m_Frame.end())
			{
				m_iCountLoop++;
				m_iterFrame = m_Frame.begin();
			}
		}
	}
	else if (m_iCountLoop < m_iNumLoop)
	{
		if (g_fAccumulation - m_fTimer >= m_iterFrame->fLifeTime)
		{
			m_fTimer = g_fAccumulation;
			m_iterFrame++;
			if (m_iterFrame == m_Frame.end())
			{
				m_iCountLoop++;
				if (m_iCountLoop <= m_iNumLoop)
				{
					m_iterFrame = m_Frame.end() - 1;
					return false;
				}
				else
					m_iterFrame = m_Frame.begin();
			}
		}
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
