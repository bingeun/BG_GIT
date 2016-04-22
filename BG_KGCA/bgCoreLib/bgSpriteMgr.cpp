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

	// 한 줄 읽고(_fgetts), 구문 분석하여 변수에 저장(_stscanf_s)
	// #SPRITE N => 스프라이트 갯수
	_fgetts(pBuffer, _countof(pBuffer), fp);
	_stscanf_s(pBuffer, _T("%s%d"), szString, _countof(szString), &iNumSprite);

	for (int iSprite = 0; iSprite < iNumSprite; iSprite++)
	{
		// XXX.bmp XXX_mask.bmp rectXXX N => 그림파일 이름, 마스크파일 이름, 스프라이트 이름, 프레임 갯수
		_fgetts(pBuffer, _countof(pBuffer), fp);
		_stscanf_s(pBuffer, _T("%s%s%s%d"), szFileName, _countof(szFileName), szFileNameMask, _countof(szFileNameMask), szString, _countof(szString), &iNumFrame);

		bgBitmap* pBitmap = I_BitmapMgr.GetPtr(szFileName);

		// 같은 이름의 스프라이트가 존재한다면 해당 갯수만큼 건너띄기
		if (pBitmap)
		{
			for (int iFrame = 0; iFrame < iNumFrame; iFrame++)
			{
				_fgetts(pBuffer, _countof(pBuffer), fp);
				// 존재하는 이름이므로 값저장 생략
				// _stscanf_s(pBuffer, _T("%d%d%d%d%d"), &iCount, &frame.rectSrc.left, &frame.rectSrc.top, &frame.rectSrc.right, &frame.rectSrc.bottom);
			}
		}
		// 같은 이름의 스프라이트가 없으면 m_List 에 추가
		else
		{
			// 지정한 그림파일 로드하기
			INT iKey = I_BitmapMgr.Add(szFileName, szFileNameMask);
			pBitmap = I_BitmapMgr.GetPtr(iKey);

			bgSprite* data = new bgSprite;
			data->Init();
			data->m_szName = szString;
			for (int iFrame = 0; iFrame < iNumFrame; iFrame++)
			{
				int iCount;
				bgFrame frame;

				// 프레임 카운트(iCount), BMP에서의 RECT(x,y,w,h)
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

