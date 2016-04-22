#include "bgSpriteMgr.h"


INT bgSpriteMgr::Add(TCHAR * pszName)
{
	FILE* fp;
	_wfopen_s(&fp, pszName, _T("rt"));
	if (fp == NULL)
		return false;

	TCHAR pBuffer[MAX_PATH] = { 0, };
	TCHAR szString[MAX_PATH] = { 0, };
	TCHAR szFileName[MAX_PATH] = { 0, };
	TCHAR szFileNameMask[MAX_PATH] = { 0, };
	int iNumSprite = 0;
	int iNumFrame = 0;

	// �� �� �а�(_fgetts), ���� �м��Ͽ� ������ ����(_stscanf_s)
	// #SPRITE N => ��������Ʈ ����
	_fgetts(pBuffer, _countof(pBuffer), fp);
	_stscanf_s(pBuffer, _T("%s%d"), szString, _countof(szString), &iNumSprite);

	for (int iSprite = 0; iSprite < iNumSprite; iSprite++)
	{
		// XXX.bmp XXX_mask.bmp rectXXX N => �׸����� �̸�, ����ũ���� �̸�, ��������Ʈ �̸�, ������ ����
		_fgetts(pBuffer, _countof(pBuffer), fp);
		_stscanf_s(pBuffer, _T("%s%s%s%d"), szFileName, _countof(szFileName), szFileNameMask, _countof(szFileNameMask), szString, _countof(szString), &iNumFrame);

		bgBitmap* pBitmap = I_BitmapMgr.GetPtr(szFileName);

		// ���� �̸��� ��������Ʈ�� �����Ѵٸ� �ش� ������ŭ �ǳʶ��
		if (pBitmap)
		{
			for (int iFrame = 0; iFrame < iNumFrame; iFrame++)
			{
				_fgetts(pBuffer, _countof(pBuffer), fp);
				// �����ϴ� �̸��̹Ƿ� ������ ����
				// _stscanf_s(pBuffer, _T("%d%d%d%d%d"), &iCount, &frame.rectSrc.left, &frame.rectSrc.top, &frame.rectSrc.right, &frame.rectSrc.bottom);
			}
		}
		// ���� �̸��� ��������Ʈ�� ������ m_List �� �߰�
		else
		{
			// ������ �׸����� �ε��ϱ�
			INT iKey = I_BitmapMgr.Add(szFileName, szFileNameMask);
			pBitmap = I_BitmapMgr.GetPtr(iKey);

			bgSprite* data = new bgSprite;
			data->Init();
			data->m_szName = szString;
			for (int iFrame = 0; iFrame < iNumFrame; iFrame++)
			{
				int iCount;
				bgFrame frame;

				// ������ ī��Ʈ(iCount), BMP������ RECT(x,y,w,h)
				_fgetts(pBuffer, _countof(pBuffer), fp);
				_stscanf_s(pBuffer, _T("%d%d%d%d%d"), &iCount, &frame.rectSrc.left, &frame.rectSrc.top, &frame.rectSrc.right, &frame.rectSrc.bottom);
				frame.pBitmap = pBitmap;
				frame.fLifeTime = DEFAULT_LIFETIME;

				data->m_Frame.push_back(frame);
			}
			m_List.insert(make_pair(m_iKeyCount++, data));
		}
	}
	fclose(fp);
	return m_iKeyCount - 1;
}

bgSprite * bgSpriteMgr::GetPtr(INT iKey)
{
	map<INT, bgSprite*>::iterator itor;

	itor = m_List.find(iKey);
	if (itor == m_List.end())
		return NULL;

	return (*itor).second;
}

bgSprite * bgSpriteMgr::GetPtr(TCHAR * szName)
{
	map<INT, bgSprite*>::iterator itor;

	for (itor = m_List.begin(); itor != m_List.end(); itor++)
	{
		if (szName == (*itor).second->m_szName)
		{
			return (*itor).second;
		}
	}
	return NULL;
}

INT bgSpriteMgr::GetKey(TCHAR * szName)
{
	map<INT, bgSprite*>::iterator itor;

	for (itor = m_List.begin(); itor != m_List.end(); itor++)
	{
		if (szName == (*itor).second->m_szName)
		{
			return (*itor).first;
		}
	}
	return NULL;
}

bool bgSpriteMgr::Release()
{
	return true;
}

bgSpriteMgr::bgSpriteMgr()
{
	m_iKeyCount = 0;
	m_List.clear();
}


bgSpriteMgr::~bgSpriteMgr()
{
	Release();
}

