#include "bgSprite.h"



bool bgSprite::Init()
{
	m_timeFrame = g_fAccumulation;
	m_iCountLoop = 0;
	return true;
}

bool bgSprite::Frame()
{
	// 무한반복 플레이 되어야 한다면... (-1)
	if (m_pFrame->m_iTotalLoop < 0)
	{
		if (g_fAccumulation - m_timeFrame >= m_iterFrame->fLifeTime)
		{
			m_timeFrame = g_fAccumulation;
			m_iterFrame++;
			// 1회 플레이가 완료되면...
			if (m_iterFrame == m_pFrame->m_vecFrame.end())
			{
				// 시작프레임으로 변경하여 다시 플레이
				m_iCountLoop++;
				m_iterFrame = m_pFrame->m_vecFrame.begin();
			}
		}
		return true;
	}
	// 유한반복이지만 플레이 횟수를 채우지 못했다면...
	else if (m_iCountLoop < m_pFrame->m_iTotalLoop)
	{
		if (g_fAccumulation - m_timeFrame >= m_iterFrame->fLifeTime)
		{
			m_timeFrame = g_fAccumulation;
			m_iterFrame++;
			// 1회 플레이가 완료되면...
			if (m_iterFrame == m_pFrame->m_vecFrame.end())
			{
				m_iCountLoop++;
				// 반복횟수만큼 플레이 되었다면
				if (m_iCountLoop <= m_pFrame->m_iTotalLoop)
				{
					// 마지막 장면에서 멈추고 false 리턴
					m_iterFrame = m_pFrame->m_vecFrame.end() - 1;
					return false;
				}
				// 반복횟수가 아직 채워지지 않았다면 시작프레임으로 변경하여 다시 플레이
				else
					m_iterFrame = m_pFrame->m_vecFrame.begin();
			}
		}
		return true;
	}
	// 플레이 횟수를 이미 채웠다면...
	return false;
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
