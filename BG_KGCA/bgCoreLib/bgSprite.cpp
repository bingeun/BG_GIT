#include "bgSprite.h"



bool bgSprite::Init()
{
	m_timeFrame = g_fAccumulation;
	m_iCountLoop = 0;
	return true;
}

bool bgSprite::Frame()
{
	// ���ѹݺ� �÷��� �Ǿ�� �Ѵٸ�... (-1)
	if (m_pFrame->m_iTotalLoop < 0)
	{
		if (g_fAccumulation - m_timeFrame >= m_iterFrame->fLifeTime)
		{
			m_timeFrame = g_fAccumulation;
			m_iterFrame++;
			// 1ȸ �÷��̰� �Ϸ�Ǹ�...
			if (m_iterFrame == m_pFrame->m_vecFrame.end())
			{
				// �������������� �����Ͽ� �ٽ� �÷���
				m_iCountLoop++;
				m_iterFrame = m_pFrame->m_vecFrame.begin();
			}
		}
		return true;
	}
	// ���ѹݺ������� �÷��� Ƚ���� ä���� ���ߴٸ�...
	else if (m_iCountLoop < m_pFrame->m_iTotalLoop)
	{
		if (g_fAccumulation - m_timeFrame >= m_iterFrame->fLifeTime)
		{
			m_timeFrame = g_fAccumulation;
			m_iterFrame++;
			// 1ȸ �÷��̰� �Ϸ�Ǹ�...
			if (m_iterFrame == m_pFrame->m_vecFrame.end())
			{
				m_iCountLoop++;
				// �ݺ�Ƚ����ŭ �÷��� �Ǿ��ٸ�
				if (m_iCountLoop <= m_pFrame->m_iTotalLoop)
				{
					// ������ ��鿡�� ���߰� false ����
					m_iterFrame = m_pFrame->m_vecFrame.end() - 1;
					return false;
				}
				// �ݺ�Ƚ���� ���� ä������ �ʾҴٸ� �������������� �����Ͽ� �ٽ� �÷���
				else
					m_iterFrame = m_pFrame->m_vecFrame.begin();
			}
		}
		return true;
	}
	// �÷��� Ƚ���� �̹� ä���ٸ�...
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
