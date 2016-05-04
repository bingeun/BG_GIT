#include "bgFrameMgr.h"


INT bgFrameMgr::Add(TCHAR * pszName)
{
	FILE* fp;
	_wfopen_s(&fp, pszName, _T("rt"));
	if (fp == NULL)
		return false;

	TCHAR pBuffer[MAX_PATH] = { 0, };
	TCHAR szString[MAX_PATH] = { 0, };
	TCHAR szFileName[MAX_PATH] = { 0, };
	TCHAR szFileNameMask[MAX_PATH] = { 0, };
	int iTotalSprite = 0;
	int iTotalFrame = 0;
	int iTotalLoop = 0;

	// �� �� �а�(_fgetts), ���� �м��Ͽ� ������ ����(_stscanf_s)
	// #SPRITE(szString) ��������Ʈ��(iTotalSprite), �׸�����(szFileName), ����ũ����(szFileNameMask)
	_fgetts(pBuffer, _countof(pBuffer), fp);
	_stscanf_s(pBuffer, _T("%s%d%s%s"), szString, _countof(szString), &iTotalSprite, szFileName, _countof(szFileName), szFileNameMask, _countof(szFileNameMask));

	for (int iSprite = 0; iSprite < iTotalSprite; iSprite++)
	{
		// ��������Ʈ�̸�(szString), �����Ӽ�(iTotalFrame), �ݺ�Ƚ��(-x����, 0�ݺ�����, +xȸ�ݺ�)
		_fgetts(pBuffer, _countof(pBuffer), fp);
		_stscanf_s(pBuffer, _T("%s%d%d"), szString, _countof(szString), &iTotalFrame, &iTotalLoop);

		bgBitmap* pBitmap = I_BitmapMgr.GetPtr(szFileName);

		// ���� �̸��� ��������Ʈ�� �����Ѵٸ� �ش� ������ŭ �ǳʶ��
		if (pBitmap)
		{
			for (int iFrame = 0; iFrame < iTotalFrame; iFrame++)
			{
				_fgetts(pBuffer, _countof(pBuffer), fp);
				// �����ϴ� �̸��̹Ƿ� ������ ����
				//_stscanf_s(pBuffer, _T("%d%f%d%d%d%d%d%d"), &iCount, &frame.fLifeTime, &frame.posDest.x, &frame.posDest.y,
				//	&frame.rectSrc.left, &frame.rectSrc.top, &frame.rectSrc.right, &frame.rectSrc.bottom);
			}
		}
		// ���� �̸��� ��������Ʈ�� ������ m_List �� �߰�
		else
		{
			// ������ �׸����� �ε��ϱ�
			INT iKey = I_BitmapMgr.Add(szFileName, szFileNameMask);
			pBitmap = I_BitmapMgr.GetPtr(iKey);

			bgFrame* data = new bgFrame;
			data->m_szName = szString;
			data->m_iTotalLoop = iTotalLoop;
			for (int iFrame = 0; iFrame < iTotalFrame; iFrame++)
			{
				int iCount;
				FRAME frame;

				// ������ ī��Ʈ(iCount), ������ ���ӽð�(fLifeTime), ��½� �߽���(x,y) BMP������ RECT(x,y,w,h)
				_fgetts(pBuffer, _countof(pBuffer), fp);
				_stscanf_s(pBuffer, _T("%d%f%d%d%d%d%d%d"), &iCount, &frame.fLifeTime, &frame.posDest.x, &frame.posDest.y,
					&frame.rectSrc.left, &frame.rectSrc.top, &frame.rectSrc.right, &frame.rectSrc.bottom);
				frame.pBitmap = pBitmap;

				data->m_vecFrame.push_back(frame);
			}
			m_List.insert(make_pair(m_iKeyCount++, data));
		}
	}
	fclose(fp);
	return m_iKeyCount - 1;
}

bgFrame * bgFrameMgr::GetPtr(INT iKey)
{
	map<INT, bgFrame*>::iterator itor;

	itor = m_List.find(iKey);
	if (itor == m_List.end())
		return NULL;

	return (*itor).second;
}

bgFrame * bgFrameMgr::GetPtr(TCHAR * szName)
{
	map<INT, bgFrame*>::iterator itor;

	for (itor = m_List.begin(); itor != m_List.end(); itor++)
	{
		if (szName == (*itor).second->m_szName)
		{
			return (*itor).second;
		}
	}
	return NULL;
}

INT bgFrameMgr::GetKey(TCHAR * szName)
{
	map<INT, bgFrame*>::iterator itor;

	for (itor = m_List.begin(); itor != m_List.end(); itor++)
	{
		if (szName == (*itor).second->m_szName)
		{
			return (*itor).first;
		}
	}
	return NULL;
}

bool bgFrameMgr::Release()
{
	return true;
}

bgFrameMgr::bgFrameMgr()
{
	m_iKeyCount = 0;
	m_List.clear();
}


bgFrameMgr::~bgFrameMgr()
{
	Release();
}

